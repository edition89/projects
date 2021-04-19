str1 = 'Bonecruncher Bloodbottler Gizzardgulper Fleshlumpeater'.split(' ')
str2 = 'one//toe//is//Like//a//Big//sausage//Loaf'.split('//')
str3 = 'hugeEars%goodbye%white%Straight_teeth%wrinkled%Face%bulb%rubber%dog'.split('%')
print(str1)
print(str2)
print(str3)
flag = 0
text = ''
for word in str1:
    print(word + ':')
    for second in str2:
        for j in second:
            if(word.find(j) != -1): flag = flag +0.5
        if(flag < 1): text = text + second.capitalize() + ' ! '
        flag = 0
    print(text[0:-3])
    text = ''
    for second in str3:
        #print(second)
        if(len(second) == 0): break
        if(word.upper().find(second[0].upper()) != -1): flag = flag + 2
        if(word.upper().find(second[-1].upper()) != -1): flag = flag + 2
        for i in second:
            if(ord(i) > 64 and ord(i) < 91):
                flag = 1
                break
        if(len(second) < 3):
            flag = 1
        if(flag > 1): text = text + second + '-0-'
        #print(flag)
        flag = 0
    print(text[0:-3])
    text = ''
            
                
        
