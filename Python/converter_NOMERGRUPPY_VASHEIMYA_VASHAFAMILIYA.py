from forex_python.converter import CurrencyRates
import datetime
c = CurrencyRates()

def change(IN, TO, quantity, d):
    print(str(c.convert(IN, TO, quantity, d))[0:5])

count = 0
get_history = []

while(1):
    print('Какую валюты вы хотите поменять?')
    IN = input()
    try:
        c.get_rates('USD')[IN]
    except KeyError:
        print('Вы ошиблись попробуйте ввести данные заново. Такой валюты нет в базе.')
        print('')
        continue
    print('На какую валюту хотите поменять?')
    TO = input()
    try:
        c.get_rates('USD')[TO]
    except KeyError:
        print('Вы ошиблись попробуйте ввести данные заново')
        print('')
        continue
    print('Сколько купюр вы хотите поменять?')
    try:
        quantity = int(input())
    except ValueError:
        print('Вы ошиблись попробуйте ввести данные заново. Количество задано не верно!')
        print('')
        continue
    print('Вы хотите произвести обмен валюты с определнной датой?')
    print('1 - Да, 0 - Нет')
    flag = input()
    if(flag == '0' or flag == '1'):
        if(flag == '1'):
            print('Введите год')
            year = input()
            print('Введите месяц')
            month = input()
            print('Введите день')
            day = input()
            try:
                year = int(year)
            except ValueError:
                print('Вы ошиблись попробуйте ввести данные заново. Дата введена неверно!')
                print('')
                continue
            if(year < 2005):                
                print('Данные о курсе валюты с этой датой неизвестны')
                print('')
                continue
            try:
                d = datetime.datetime(year, int(month), int(day))
            except ValueError:
                print('Вы ошиблись попробуйте ввести данные заново. Дата введена неверно!')
                print('')
                continue
            except SyntaxError:
                print('Вы ошиблись попробуйте ввести данные заново. Дата введена неверно!')
                print('')
                continue
        if(flag == '0'):
            d = datetime.datetime.now()
    else:
        print('Вы ошиблись попробуйте ввести данные заново. Вы не верно выбрали ответ на вопрос. ')
        print('')
        continue
    print('')
    text = 'Конвертировал ' + str(quantity) + ' ' + IN + ' в ' + TO + ' по курсу ' + str(c.get_rate(IN, TO))[0:5] + ' за ' + str(d.day) + '.' + str(d.month) + '.' + str(d.year) + ' и получил ' + str(c.convert(IN, TO, quantity))[0:5]
    get_history.append(text)
    change(IN, TO, quantity, d)
    print('Повторить операцию?')
    print('1 - Да, 0 - Нет')
    flag = input()
    if(flag == '0' or flag == '1'):
        if(flag == '0'):
            print('До свидания!')
            break
    else:
        print('Вы ошиблись попробуйте ввести данные заново. Вы не верно выбрали ответ на вопрос. ')
        print('')
        continue


