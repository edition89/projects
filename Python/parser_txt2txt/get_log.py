# -*- coding: utf-8 -*
from bs4 import BeautifulSoup
import requests
import re

INPUT_FILE = "ip_list.txt"
HEADERS = {"User-Agent": "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.2.8) Gecko/20100722 Firefox/3.6.8 GTB7.1 (.NET CLR 3.5.30729)", "Referer": "http://example.com"}
ip_list = [line.strip() for line in open(INPUT_FILE, 'r', encoding='utf8').readlines()]
my_socks= {
    'state': 0,
    'ip': 'Место ввода данных',
    'port': 'Место ввода данных',
    'login': 'Место ввода данных',
    'pass': 'Место ввода данных',
    }
for item in ip_list:
    URL = item
    pattern = re.search('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', item)[0]
    try:
        try:
            if(my_socks['state'] == 1):
                response = requests.get(URL, headers = HEADERS, verify=False,
                                        proxies=dict(http='socks5://' + my_socks['login'] + ':' + my_socks['pass'] + '@' + my_socks['ip'] + ':' + my_socks['port'],
                                                     https='socks5://' + my_socks['login'] + ':' + my_socks['pass'] + '@' + my_socks['ip'] + ':' + my_socks['port']))
            elif(my_socks['state'] == 0):
                response = requests.get(URL, headers = HEADERS, verify=False)
            
        except requests.exceptions.ConnectionError:
            response.status_code = "Connection refused"
        if(response.status_code == 200 ):
            soup = BeautifulSoup(response.content, 'html.parser')
            file = open(pattern.replace('.', '_') + '.txt', 'w+', encoding='utf8')
            print(soup)
            file.write(str(soup))
            file.close()
        else:
            print('Status code = ' + str(response.status_code) + ' next ip.')
    except requests.exceptions.ConnectTimeout:
        print('Web site does not exist')
    

