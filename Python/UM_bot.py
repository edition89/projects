
#token='33a9a82f77bf742fc80292d35da5750d21a5b962f8716859457ace67c1f5f800a9677ddcad428ed23e546'

# -*- coding: utf-8 -*-
from vk_api import VkApi, VkUpload
from vk_api.bot_longpoll import VkBotLongPoll, VkBotEventType
from vk_api.keyboard import VkKeyboard, VkKeyboardColor
from vk_api.utils import get_random_id


vk_session = VkApi(token='33a9a82f77bf742fc80292d35da5750d21a5b962f8716859457ace67c1f5f800a9677ddcad428ed23e546')
longpoll = VkBotLongPoll(vk_session, 196410704)
upload = VkUpload(vk_session)
vk = vk_session.get_api()


def send_message(event):
    vk.messages.send(
                random_id=get_random_id(),
                peer_id=event.object.message['peer_id'],
                message=event.object.message['text'],
            )

def keyboard(event):
    keyboard = VkKeyboard(one_time=False)
    keyboard.add_button('Я знаю песню!', color=VkKeyboardColor.DEFAULT)
    vk.messages.send(
        peer_id=event.object.message['peer_id'],
        random_id=get_random_id(),
        keyboard=keyboard.get_keyboard(),
        message='Клава готова'
    )

def answer(event):
    vk.messages.send(
                random_id=get_random_id(),
                peer_id=event.object.message['peer_id'],
                message= '@' + str(event.object.message['peer_id']) + ' был первым'
                )
    
def main():
    for event in longpoll.listen():
        if event.type == VkBotEventType.MESSAGE_NEW or event.from_chat:
            request = event.object.message['text']      
            print(event.object.message['from_id'])
            if(request == '[club196410704|@1kirkorov] Клава'):
                keyboard(event)
            elif(request == '[club196410704|@1kirkorov] Я знаю песню!' or request == 'Я знаю песню!') :
                answer(event)
            
            elif(request == '[club196410704|@1kirkorov] Помощь'):
                vk.messages.send(
                random_id=get_random_id(),
                peer_id=event.object.message['peer_id'],
                message='Нужна помощь? Я известная личность и у меня не так много времени, поэтому напиши "@1kirkorov Клава" дальше сам разберешься'
                )
            else:
                vk.messages.send(
                random_id=get_random_id(),
                peer_id=event.object.message['peer_id'],
                message='Походи еще чуть чуть',
            )


if __name__ == '__main__':
    main()
