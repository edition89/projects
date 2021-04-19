#!/usr/bin/env python3
import csv
import os
import re 

f = open('deps.txt', 'r', encoding='utf-8').read()
text = ''
myData = []
myData.append([])
count = 0
flag_text = 0

text = re.sub(r'№\s.{0,}','', f)
text = re.sub(r'\s{0,}:\s{0,}',':', text)
f = ''
for i in text.split('\n'):
    if(len(i) > 0 and i.find(':') != -1):
        f = f + i + '\n'
        flag_text = 1
        continue
    if(len(i) > 0 and flag_text == 1):
        f = f[:-1] + ', ' + i + '\n'
for i in f[0:-1].split('\n'):
    if(i.split(':')[0] == 'Логин'):
        myData.append([])
        count = count + 1
    if(not(i.split(':')[0] in myData[0])):
        myData[0].append(i.split(':')[0])
    if(len(myData[0]) > len(myData[count])):
        myData[count].append('')
    myData[count].insert([myData[0].index(i.split(':')[0])][0],i.split(':')[1])
  
myFile = open('example2.csv', 'w')
with myFile:
    writer = csv.writer(myFile)
    writer.writerows(myData)
    
print("Writing complete")
