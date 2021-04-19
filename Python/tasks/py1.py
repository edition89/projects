import random
#Начальные переменные
arr = [] #Массив
len_arr = 20 #Длина массива
range_arr = 20 # Диапазон массива от 0 до 
#Цикл создания случайного массива
for i in range(len_arr):
    arr.append(random.randint(0, range_arr))
print("Массив:", end=' ')
#Вывод элементов массива
print(arr)
#Сортировка массива методом пузыря
for i in range(len_arr-1):
    for j in range(len_arr-i-1):
        if arr[j] > arr[j+1]:
            arr[j], arr[j+1] = arr[j+1], arr[j]           
#Вывод элементов массива
print("Отсартированный массив:", end=' ')
print(arr)
#Удаление повторяющих элементов массива
a = [] 
for x in arr:
    if not x in a:
        a.append(x)
#Вывод элементов сортированого массива без повторяющих элементов
print("Отсартированный массив без повторяющих элементов:", end=' ')
print(a)
