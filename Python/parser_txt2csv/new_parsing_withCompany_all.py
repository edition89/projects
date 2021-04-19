#!/usr/bin/env python3
import csv
import os
import re

file_list = []
myData = []
myData.append([])
flag_key = 1
flag_text = 0
count = 0
for root, dirs, files in os.walk("."):  
    for filename in files:
        if(filename.find('.txt') != -1):
            file_list.append(filename)
            count = count + 1
for j in range(count): 
    f = open(file_list[j], 'r', encoding='utf-8').read()
    text = ''
    text = re.sub(r'\s{0,}:\s{0,}',':', f)
    f = ''
    for i in text.split('\n'):
        if(len(i) > 0 and i.find(':') != -1):
            f = f + i + '\n'
            flag_text = 1
            continue
        if(len(i) > 0 and flag_text == 1):
            f = f[:-1] + ', ' + i + '\n'
    f = f.split('\n')
    for i in f:
        if(flag_key):
            myData[0].append(i.split(':')[0])
        else:
            if(not (i.split(':')[0]) in myData[0]):
                myData[0].append(i.split(':')[0])
    flag_text = 0
    flag_key = 0
    myData[0].pop(myData[0].index(''))
    myData.append([])
    for i in range(len(myData[0])):
        myData[j + 1].append('')
    for i in f:
        if(i == ''): break
        myData[j + 1][myData[0].index(i.split(':')[0])] = i.split(':')[1]
print(len(myData))
myFile = open('example2.csv', 'w')
with myFile:
    writer = csv.writer(myFile)
    writer.writerows(myData)
    
print("Writing complete")
