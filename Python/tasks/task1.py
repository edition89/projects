arr = []
while(1):
    arr.append(int(input()))
    if(len(arr) > 1 and arr[0] > arr[-1]): break
for i in range(1, len(arr) - 1):
    print('Лучников ' + str(arr[i] // arr[0]) + ';')
