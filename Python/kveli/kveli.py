#!/usr/bin/env python3
#https://github.com/FlymeDllVa/telebot-calendar

import os
import time
import datetime
import calendar
import logging
import telebot
import emoji
import pandas as pd

import inline_calendar
from inline_calendar import CallbackData
from telebot import types
#from telebot import apihelper
from emoji import emojize
from multiprocessing import *
import schedule

os.environ["TZ"] = "Europe/Moscow"
time.tzset()

def start_process():#Запуск Process
    p1 = Process(target=P_schedule.start_schedule, args=()).start()


class P_schedule(): # Class для работы с schedule
    def start_schedule(): #Запуск schedule
        ######Параметры для schedule######
        schedule.every(60).minutes.do(P_schedule.send_message3)
        if(time.localtime().tm_hour >= 11 and time.localtime().tm_hour <= 23):
            schedule.every().day.at("11:00").do(P_schedule.send_message2)
            schedule.every().day.at("14:00").do(P_schedule.send_message2)
            schedule.every().day.at("17:00").do(P_schedule.send_message2)
            schedule.every().day.at("20:00").do(P_schedule.send_message2)
            schedule.every().day.at("23:00").do(P_schedule.send_message2)
            #schedule.every(180).minutes.do(P_schedule.send_message2)
        ##################################

        while True: #Запуск цикла
            schedule.run_pending()
            time.sleep(1)

    ####Функции для выполнения заданий по времени
    def send_message1():
        bot.send_message(965078476, 'Отправка сообщения по времени') #965078476 id kveli, 793923786 my id
    def send_message2():
        bot.send_message(965078476, 'Привет автомониторинг Бота, все в порядке!')
    def send_message3():
        bot.send_message(793923786, 'Привет автомониторинг Бота, все в порядке!')
    ################

handle = open(os.path.abspath(__file__).replace('kveli.py', '') + "mat.txt", "r")
token = open(os.path.abspath(__file__).replace('kveli.py', '') + "token.txt", "r")
data = handle.readlines()
data = ''.join(data).split(', ')

#number = ''

#apihelper.proxy = {'https':'socks5://163.172.147.132:1080'}
bot = telebot.TeleBot(token);

logging.basicConfig(filename="sample.log", level=logging.ERROR,
                    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')

logger = logging.getLogger(__name__)

calendar_1 = CallbackData("calendar_1", "action", "year", "month", "day")
info = {'phone': '', 'fio': '', 'date': '', 'time': '', 'place': '', 'people': ''}

@bot.callback_query_handler(func=lambda call: call.data and call.data.startswith('back'))
def callback_back(call: types.CallbackQuery):
        bot.clear_step_handler_by_chat_id(chat_id=call.message.chat.id)
        bot.delete_message(call.message.chat.id, call.message.message_id)
        bot.delete_message(call.message.chat.id, call.message.message_id-1)
        bot.register_next_step_handler(call.message, get_fio);

@bot.callback_query_handler(func=lambda call: call.data.startswith(calendar_1.prefix))
def callback_inline(call: types.CallbackQuery):
    global info
    name, action, year, month, day = call.data.split(calendar_1.sep)
    date = inline_calendar.calendar_query_handler(
        bot=bot, call=call, name=name, action=action, year=year, month=month, day=day
    )
    if action == "DAY":
        if datetime.date(date.year, datetime.datetime.now().month, datetime.datetime.now().day).toordinal() > datetime.date(datetime.datetime.now().year, date.month, date.day).toordinal():
            now = datetime.datetime.now()
            bot.answer_callback_query(call.id, text='Выбрана неверная дата', show_alert=False)
            bot.send_message(
                call.message.chat.id,
                "Выберите желаемую дату посещения",
                reply_markup=inline_calendar.create_calendar(
                name=calendar_1.prefix,
                year=now.year,
                month=now.month,  # Specify the NAME of your calendar
                    ),
            )
        else:
            #bot.send_message(
            #    chat_id=call.from_user.id,
            #    text=f"Выбранная дата  {date.strftime('%d.%m.%Y')}",
            #    reply_markup=types.ReplyKeyboardRemove(),
            #)
            types.ReplyKeyboardRemove()
            info['date'] = str(date.day) + '-' + str(date.month) + '-' + str(date.year)
            get_hour(call)
            #get_place(call, '')
            #print(f"{calendar_1}: Day: {date.strftime('%d.%m.%Y')}")
    elif action == "CANCEL":
        bot.send_message(
            chat_id=call.from_user.id,
            text="Генацвале, начнём? введи команду /start",
            reply_markup=types.ReplyKeyboardRemove(),
        )

@bot.callback_query_handler(func=lambda call: call.data and call.data.startswith('place'))
def callback_place(call: types.CallbackQuery):
    if call.data != 'place4':
        types.ReplyKeyboardRemove()
        global info
        info['place'] = call.data[5:]
        if call.data == 'placePepperBar':
            get_hour(call)
        else:
            get_hour(call)
    else:
        bot.send_message(call.message.chat.id, 'Выберите дату:', reply_markup = types.ReplyKeyboardRemove())
        bot.delete_message(call.message.chat.id, call.message.message_id)
        bot.delete_message(call.message.chat.id, call.message.message_id+1)
        now = datetime.datetime.now()
        bot.send_message(
        call.message.chat.id,
        "Выберите дату",
        reply_markup=inline_calendar.create_calendar(
            name=calendar_1.prefix,
            year=now.year,
            month=now.month,  # Specify the NAME of your calendar
            ),
        )

@bot.callback_query_handler(func=lambda call: call.data and call.data.startswith('btn'))
def callback_hour(call: types.CallbackQuery):
    if call.data != 'btnback':
        types.ReplyKeyboardRemove()
        global info
        info['time'] = call.data[3:]
        get_people(call)
    else:
        bot.delete_message(call.message.chat.id, call.message.message_id)
        types.ReplyKeyboardRemove();
        now = datetime.datetime.now()
        bot.send_message(
        call.message.chat.id,
        "Выберите дату",
        reply_markup=inline_calendar.create_calendar(
            name=calendar_1.prefix,
            year=now.year,
            month=now.month,  # Specify the NAME of your calendar
            ),
        )

@bot.callback_query_handler(func=lambda call: call.data and call.data.startswith('data'))
def callback_choose(call: types.CallbackQuery):
    #print(call.data)
    #global number
    if call.data == 'dataYes':
        #bot.send_message(call.message.chat.id, "Выберите дату", reply_markup = types.ReplyKeyboardRemove())
        #bot.delete_message(call.message.chat.id, call.message.message_id)
        bot.delete_message(call.message.chat.id, call.message.message_id)
        now = datetime.datetime.now()
        bot.send_message(
        call.message.chat.id,
        "Выберите дату",
        reply_markup=inline_calendar.create_calendar(
            name=calendar_1.prefix,
            year=now.year,
            month=now.month,  # Specify the NAME of your calendar
            ),
        )
    elif call.data == 'dataNo':
        #Укажите ваш номер телефона
        #Дорогой гость, давайте познакомимся, как Вас зовут?
        #number = ''
        bot.delete_message(call.message.chat.id, call.message.message_id)
        bot.clear_step_handler_by_chat_id(chat_id=call.message.chat.id)
        bot.send_message(call.message.chat.id, "Укажите ваш номер телефона" ,reply_markup=cancel())
        bot.register_next_step_handler(call.message, get_fio);
    elif call.data == 'dataCancel':
        bot.delete_message(call.message.chat.id, call.message.message_id)
        bot.clear_step_handler_by_chat_id(chat_id=call.message.chat.id)
        bot.send_message(call.message.chat.id, "Генацвале, начнём?" ,reply_markup=keyboard());

@bot.callback_query_handler(func=lambda call: call.data and call.data.startswith('people'))
def callback_people(call: types.CallbackQuery):
    if call.data != 'people4':
        bot.delete_message(call.message.chat.id, call.message.message_id)
        types.ReplyKeyboardRemove()
        global info
        info['people'] = call.data[6:]
        bot.send_message(call.message.chat.id,'Выбранная дата: ' + info['date'] + '\nВыбранный час: ' + info['time'] + '\nКоличество посетителей: ' + info['people'],reply_markup=keyboard());
        bot.send_message(call.message.chat.id, emoji.emojize('Спасибо ' + info['fio'] + ' :Georgia:\nСкоро наш администратор свяжется с Вами для подтверждения брони.'),reply_markup=keyboard());
        bot.send_message('965078476', 'Телефон: ' + str(info['phone']) + '\nФИО: ' + info['fio'] + '\nДата: ' + str(info['date']) + '\nВремя: ' + str(info['time']) + '\nКоличество человек: ' + info['people']);
        df = pd.read_csv('data_base.csv', sep = ',')
        dfRow = df.loc[df['id'] == call.message.chat.id]
        #global number
        if len(dfRow.index) == 0:
            #print('First')
            #columns = ['id', 'name', 'phone']
            #data = [call.message.chat.id, info['fio'], info['phone']]

            df = pd.DataFrame({"id": call.message.chat.id, "name": info['fio'], "phone": info['phone']}, index=[0])

            #df = pd.DataFrame(data, columns=columns)
            df.to_csv(r'data_base.csv', mode='a', header=False, index=False)
            #df.loc[len(df)] = ['\n' + str(call.message.chat.id), info['fio'], info['phone']]
            #df.to_csv(r'data_base.csv', mode='a', header=None, index=False)

        else:
            #print(dfRow.index)
            df.iat[dfRow.index[0], 1] = info['fio']
            df.iat[dfRow.index[0], 2] = info['phone']
            #df = pd.DataFrame({"id": call.message.chat.id, "name": info['fio'], "phone": info['phone']}, index=dfRow.index)
            #df.set_value(dfRow.index[0], 'name', info['fio'])
            #df.set_value(dfRow.index[0], 'phone', info['phone'])
            df.to_csv('data_base.csv', index=False)
        #number = ''

    else:
        #bot.send_message(call.message.chat.id, 'Выберите дату:', reply_markup = types.ReplyKeyboardRemove())
        bot.delete_message(call.message.chat.id, call.message.message_id)
        #bot.delete_message(call.message.chat.id, call.message.message_id+1)
        get_hour(call)

@bot.callback_query_handler(func=lambda call: call.data and call.data.startswith('cancel'))
def callback_cancel(call: types.CallbackQuery):
    bot.delete_message(call.message.chat.id, call.message.message_id)
    bot.clear_step_handler_by_chat_id(chat_id=call.message.chat.id)
    bot.send_message(call.message.chat.id, 'Генацвале, начнём?' ,reply_markup=keyboard());

@bot.message_handler(commands=['start'])
def send_welcome(message):
    bot.clear_step_handler_by_chat_id(chat_id=message.chat.id)
    try:
        bot.send_message(message.from_user.id, 'Генацвале, начнём?',reply_markup=keyboard());
    except:
        pass

@bot.message_handler(content_types=['text'])
def start(message):
    if message.text.find('Забронировать стол') > -1:

        df = pd.read_csv('data_base.csv', sep = ',')
        dfRow = df.loc[df['id'] == message.from_user.id]
        #global number
        if len(dfRow.index) != 0:
            #print('Yes')
            dfName = df.loc[dfRow.index[0], 'name']
            dfPhone = df.loc[dfRow.index[0], 'phone']
            info['fio'], info['phone'] = dfName, dfPhone
            bot.send_message(message.from_user.id, 'Вы хотите оставить прежние данные? \nФИО: ' + str(dfName) + '\nТелефон: ' + str(dfPhone),reply_markup = keyboard_inline_choose());
        else:
            bot.clear_step_handler_by_chat_id(chat_id=message.chat.id)
            bot.send_message(message.from_user.id, "Укажите ваш номер телефона",reply_markup = cancel());

            #bot.delete_message(message.chat.id, message.message_id+1)
            #bot.send_message(message.from_user.id, "Укажите ваш номер телефона",reply_markup = cancel())
            bot.register_next_step_handler(message, get_fio);
    elif message.text.find('Контакты') > -1:
        bot.clear_step_handler_by_chat_id(chat_id=message.chat.id)
        bot.send_message(message.from_user.id, emoji.emojize(":telephone_receiver: 228-078"),reply_markup=keyboard_inline_social());
        bot.send_location(message.from_user.id,56.150965, 47.249740)
    elif message.text.find('О Ресторане') > -1:
        bot.clear_step_handler_by_chat_id(chat_id=message.chat.id)
        bot.send_message(message.from_user.id, "ГАМАРДЖОБА! \nМЫ РАДЫ ВИДЕТЬ ВАС В НАШЕМ ГРУЗИНСКОМ ДОМЕ «КВЕЛИ»! \n"
                                                            + emoji.emojize(":red_heart: :Georgia:") + "\n"
                                                            + "Чтобы воссоздать частичку Грузии в Чебоксарах, наша команда отправилась изучать самую гостеприимную и колоритную страну. "
                                                            + "Край, знаменитый своей кухней, виноделием и радушием, покорил нас и познакомил с самобытной культурой и традициями. "
                                                            + "Мы искренне хотим поделиться с Вами вкусом и тёплыми эмоциями, привезёнными в родной город. " + emoji.emojize(":smiling_face_with_halo:") + "\n"
                                                            + "Грузинский народ говорит: «Квели да пури - кетили гули» - «Сыр и хлеб - да доброе сердце». "
                                                            + "Именно эта поговорка и выражает отношение грузинского народа к еде! «Квели», т.е. сыр - самая основа грузинской кухни и рациона, столь же необходима, как хлеб, «пури». "
                                                            + "Наслаждайтесь нашим сыром и хлебом собственного производства!\nПоднимайте бокал ароматного грузинского вина за любовь, семью, Родину и за всех, кто собрался за столом!" + emoji.emojize(":bottle_with_popping_cork:") + "\n"
                                                            + "Теперь мы предлагаем вам полностью погрузиться в нашу уютную атмосферу и отправиться в невероятное гастропутешествие.\nГУАМАРДЖОС!" + emoji.emojize(":red_heart: :Georgia:"),reply_markup=keyboard());
    elif message.text.find('Наше меню') > -1:
        bot.clear_step_handler_by_chat_id(chat_id=message.chat.id)

        #media = [types.InputMediaPhoto("bar1.jpg"),types.InputMediaPhoto("bar2.jpg")]
        #bot.send_media_group(message.chat.id, media)

        #telegram.InputMediaPhoto
        #print(types.InputMediaPhoto("bar2.jpg"))
        #img1 = open('bar1.jpg', 'rb')
        #img2 = open('bar2.jpg', 'rb')
        #bot.send_photo(message.chat.id, img1)
        #bot.send_photo(message.chat.id, img2)
        with open(os.path.abspath(__file__).replace('kveli.py', '') + 'menu1.jpg', 'rb') as img1, open(os.path.abspath(__file__).replace('kveli.py', '') + 'menu2.jpg', 'rb') as img2, open(os.path.abspath(__file__).replace('kveli.py', '') + 'menu3.jpg', 'rb') as img3:
            #files = bot.send_media_group(message.from_user.id, [types.InputMediaPhoto(img1),"text\n", types.InputMediaPhoto(img2)]) Основная команда отправка медиа файлов
            bot.send_media_group(message.from_user.id, [types.InputMediaPhoto(img1)])
            #bot.send_message(message.from_user.id, "_______________________________________\n");
            bot.send_media_group(message.from_user.id, [types.InputMediaPhoto(img2)])
            #bot.send_message(message.from_user.id, "_______________________________________\n");
            bot.send_media_group(message.from_user.id, [types.InputMediaPhoto(img3)])
        doc = open(os.path.abspath('menu.pdf'), 'rb')
        bot.send_document(message.from_user.id, doc)
        bot.send_document(message.from_user.id, "FILEID")
    elif message.text.find('Оставить отзыв') > -1:
        bot.clear_step_handler_by_chat_id(chat_id=message.chat.id)
        bot.send_message(message.from_user.id, 'Напиши свой отзыв о ресторане:' , reply_markup = cancel());
        cancel();
        #bot.delete_message(message.chat.id, message.message_id+1)
        #bot.send_message(message.from_user.id, 'Напиши свой отзыв о ресторане:' , reply_markup = cancel());
        bot.register_next_step_handler(message, get_feedback);
    elif message.text == 'Отмена':
        bot.clear_step_handler_by_chat_id(chat_id=message.chat.id)
        keyboard();
    elif message.text == 'easteregg':
        bot.send_message(message.from_user.id, 'Разработчки' , reply_markup = keyboard())
        bot.send_message(message.from_user.id, 'https://instagram.com/gabibullae');
    else:
        try:
            bot.send_message(message.from_user.id, 'Напиши /start');
        except:
            pass

def calendar(message):
    global info;
    info['fio'] = message.text
    now = datetime.datetime.now()  # Get the current date
    bot.send_message(
        message.chat.id,
        "Выберите дату:",
        reply_markup=inline_calendar.create_calendar(
            name=calendar_1.prefix,
            year=now.year,
            month=now.month,  # Specify the NAME of your calendar
        ),
    )

def get_fio(message):
    count = 0
    #global number
    for i in range(len(message.text)):
        if message.text[i] >= '0' and message.text[i] <= '9':
            count += 1
            #number = number + message.text[i]
    if count == 6 or count == 10 or count == 11:
        global info
        info['phone'] = str(message.text)
        bot.send_message(message.from_user.id, 'Дорогой гость, давайте познакомимся, как Вас зовут?', reply_markup = back())
        bot.register_next_step_handler(message, get_calendar);
    else:
        bot.send_message(message.from_user.id, 'Телефон введен неверно. Попробуйте забронировать стол снова.', reply_markup = keyboard())
        return 0


def get_place(call, back):
    global info
    if back == 'back':
        bot.send_message(call.message.chat.id, 'Условия брони:', reply_markup = types.ReplyKeyboardRemove())
        bot.delete_message(call.message.chat.id, call.message.message_id)
        bot.delete_message(call.message.chat.id, call.message.message_id+1)
    else:
        bot.send_message(call.message.chat.id, 'Условия брони:', reply_markup = types.ReplyKeyboardRemove())
        bot.delete_message(call.message.chat.id, call.message.message_id+1)
    bot.send_message(call.message.chat.id, emoji.emojize('Условия брони:\n:woman_dancing: Main Place (Основной танцпол) -\nПт&Сб: депозит 2.000р\nВск-Чт: без депозита.\n:studio_microphone: Pesni Bar (Караоке-зал) -\nПт&Сб: депозит 2.000р\nВск-Чт: без депозита.\n:tropical_drink: Pepper Bar (Лаунж-зал) -\nПт&Сб: без депозита.\nВыбери зал, который тебе подходит:\nВыбранная дата: ' + info['date']), reply_markup = keyboard_inline_place())

def get_hour(call):
    global info
    #bot.send_message(call.message.chat.id, 'Пожалуйста, выберите час:', reply_markup = types.ReplyKeyboardRemove())
    day_w, month_w, year_w = (int(x) for x in info['date'].split('-'))
    ans = datetime.date(year_w, month_w, day_w)
    w_day = ans.strftime("%A")
    #bot.delete_message(call.message.chat.id, call.message.message_id)
    #bot.delete_message(call.message.chat.id, call.message.message_id)
    bot.send_message(call.message.chat.id, 'Пожалуйста, выберите час:\nВыбранная дата: ' + info['date'], reply_markup = keyboard_inline(w_day))

def get_people(call):
    global info
    #bot.send_message(call.message.chat.id, 'Сколько гостей ожидается за столом?', reply_markup = types.ReplyKeyboardRemove())
    bot.delete_message(call.message.chat.id, call.message.message_id)
    #bot.delete_message(call.message.chat.id, call.message.message_id+1)
    bot.send_message(call.message.chat.id, 'Сколько гостей ожидается за столом?\nВыбранная дата: ' + info['date'] + '\nВыбранный час: ' + info['time'], reply_markup = keyboard_inline_people())

def get_calendar(message):
    global data
    if message.text.lower() in data:
        bot.send_message(message.from_user.id, 'Очень приятно ' + message.text + '! Может вы ошибились и вас зовут иначе? Попробуйте забронировать стол снова.', reply_markup = keyboard())
        return 0
    #bot.send_message(message.from_user.id,'Рад приветствовать ' + message.text,reply_markup=calendar(message));
    calendar(message);

def get_feedback(message):
    bot.send_message(message.chat.id, 'Спасибо за ваш отзыв!', reply_markup = keyboard())
    bot.send_message('965078476', 'Отзыв:\n' + message.text);
    #bot.forward_message('@gabibullae_bot', '@gabibullaeforward', message.message_id)

def back():
    in_markup = types.InlineKeyboardMarkup()
    in_btn1 = types.InlineKeyboardButton('Назад', callback_data='back')
    in_markup.add(in_btn1)
    return in_markup

def cancel():
    in_markup = types.InlineKeyboardMarkup()
    in_btn1 = types.InlineKeyboardButton('Отмена', callback_data='cancel')
    in_markup.add(in_btn1)
    return in_markup

def send_tel():
    markup = types.ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    btn1 = types.KeyboardButton('Оставить телефон', request_contact = True)
    btn2 = types.KeyboardButton('Назад')
    markup.add(btn1)
    markup.add(btn2)
    return markup

def keyboard():
    markup = types.ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    btn1 = types.KeyboardButton(emoji.emojize(':fork_and_knife_with_plate: Забронировать стол :fork_and_knife_with_plate:'))
    btn2 = types.KeyboardButton(emoji.emojize(':information: О Ресторане :information:'))
    btn3 = types.KeyboardButton(emoji.emojize(':open_book: Наше меню :open_book:'))
    btn4 = types.KeyboardButton(emoji.emojize(':mobile_phone: Контакты :mobile_phone:'))
    btn5 = types.KeyboardButton(emoji.emojize(':writing_hand: Оставить отзыв :writing_hand:'))
    markup.add(btn1)
    markup.add(btn2)
    markup.add(btn3)
    markup.add(btn4)
    markup.add(btn5)
    return markup

def keyboard_inline(w_day):
    in_markup = types.InlineKeyboardMarkup(row_width=4)

    #in_btn1 = types.InlineKeyboardButton('11.00', callback_data='btn11.00')
    #in_btn2 = types.InlineKeyboardButton('12.00', callback_data='btn12.00')
    #in_btn3 = types.InlineKeyboardButton('13.00', callback_data='btn13.00')
    #in_btn4 = types.InlineKeyboardButton('14.00', callback_data='btn14.00')
    #in_btn5 = types.InlineKeyboardButton('15.00', callback_data='btn15.00')
    #in_btn6 = types.InlineKeyboardButton('16.00', callback_data='btn16.00')
    in_btn7 = types.InlineKeyboardButton('17.00', callback_data='btn17.00')
    in_btn8 = types.InlineKeyboardButton('18.00', callback_data='btn18.00')
    in_btn9 = types.InlineKeyboardButton('19.00', callback_data='btn19.00')
    in_btn10 = types.InlineKeyboardButton('20.00', callback_data='btn20.00')
    in_btn11 = types.InlineKeyboardButton('21.00', callback_data='btn21.00')
    in_btn12 = types.InlineKeyboardButton('22.00', callback_data='btn22.00')
    in_btn13 = types.InlineKeyboardButton('Назад', callback_data='btnback')

    #in_markup.add(in_btn1, in_btn2, in_btn3, in_btn4,)
    in_markup.add(in_btn7, in_btn8, in_btn9)
    in_markup.add(in_btn10, in_btn11, in_btn12)
    if(w_day == "Saturday" or w_day == "Sunday"):
        in_markup.add(types.InlineKeyboardButton('23.00', callback_data='btn23.00'))
    in_markup.add(in_btn13)
    return in_markup

def keyboard_inline_place():
    in_markup = types.InlineKeyboardMarkup()
    in_btn1 = types.InlineKeyboardButton('Main Place, танцпол - 1 и 2 этаж', callback_data='placeMainPlace')
    in_btn2 = types.InlineKeyboardButton('Pesni Bar - караоке-зал', callback_data='placePesniBar')
    in_btn3 = types.InlineKeyboardButton('Pepper Bar - лаунж-зал на 3 этаже', callback_data='placePepperBar')
    in_btn4 = types.InlineKeyboardButton('Назад', callback_data='place4')
    in_markup.add(in_btn1)
    in_markup.add(in_btn2)
    in_markup.add(in_btn3)
    in_markup.add(in_btn4)
    return in_markup

def keyboard_inline_people():
    in_markup = types.InlineKeyboardMarkup()
    in_btn1 = types.InlineKeyboardButton('1-3', callback_data='people1-3')
    in_btn2 = types.InlineKeyboardButton('3-6', callback_data='people3-6')
    in_btn3 = types.InlineKeyboardButton('7+', callback_data='people7+')
    in_btn4 = types.InlineKeyboardButton('Назад', callback_data='people4')
    in_markup.add(in_btn1,in_btn2,in_btn3)
    in_markup.add(in_btn4)
    return in_markup

def keyboard_inline_choose():
    in_markup = types.InlineKeyboardMarkup()
    in_btn1 = types.InlineKeyboardButton('Да', callback_data='dataYes')
    in_btn2 = types.InlineKeyboardButton('Нет', callback_data='dataNo')
    in_btn3 = types.InlineKeyboardButton('Отмена', callback_data='dataCancel')
    in_markup.add(in_btn1)
    in_markup.add(in_btn2)
    in_markup.add(in_btn3)
    return in_markup
def keyboard_inline_social():
    in_markup = types.InlineKeyboardMarkup()
    in_btn1 = types.InlineKeyboardButton('VK', url='https://vk.com/kveli_rest')
    in_btn2 = types.InlineKeyboardButton('Instagram', url='https://instagram.com/kveli_rest/')
    in_btn3 = types.InlineKeyboardButton('Сайт доставки', url='http://kveli.ru')
    in_markup.add(in_btn1,in_btn2)
    in_markup.add(in_btn3)
    return in_markup

if __name__ == '__main__':
    print(time.localtime().tm_wday)
    start_process()
    try:
        bot.polling(none_stop=True)
    except:
        pass
