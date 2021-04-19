# -*- coding: utf-8 -*
import os
import re

files = os.listdir()
text = ''
for file in files:
    pattern = re.search('\d{1,3}\_\d{1,3}\_\d{1,3}\_\d{1,3}\.txt',file)
    if(pattern != None):
        f = open(file[pattern.start():pattern.end()], 'r', encoding='utf-8').read()
        for f1 in f:
            if(ord(f1) > 31 and ord(f1) < 127):
                text = text + f1
        find_text = re.split('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}',text)
        find_ip = re.findall('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}',text)
        if(find_ip == None): text = f
        else:
            f = find_text[0]
            for i in range(len(find_text) - 1):
                f = f + '\n' + find_ip[i] + find_text[i + 1]
        f1 = open(file[pattern.start():pattern.end()-4] + '_parser.txt', 'w', encoding='utf-8')
        f1.write(f)
        f1.close()

