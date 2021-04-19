import math

print("Выбирите фигуру:\n1: Круг;\n2: Квадрат;\n3: Прямоугольник;" + 
      "\n4: Треугольник(прямоугольный);\n5: Треугольник(равносторонний);\n6: Треугольник(равнобедренный);\n7: Ромб;\n8: Правильный многоугольник;")
figure = input()
def print_param(P, S):
    print("Периметр равен: " + str(P))
    print("Площадь равна: " + str(S))

if(figure == '1'):
    R = int(input("Введите радиус: "))
    P = 2 * math.pi * R
    S = math.pi * R * R
    print_param(P, S)
elif(figure == '2'):
    A = int(input("Введите стороны a: "))
    P = A * 4
    S = A * A
    print_param(P, S)
elif(figure == '3'):
    A = int(input("Введите сторону a: "))
    B = int(input("Введите сторону b: "))
    P = A * 2 + B * 2
    S = A * B
    print_param(P, S)
elif(figure == '4'):
    A = int(input("Введите первый катет: "))
    B = int(input("Введите второй катет: "))
    C = math.sqrt(A * A + B * B)
    P = A + B + C
    S = (A * B) / 2
    print_param(P, S)
elif(figure == '5'):
    A = int(input("Введите стороны a: "))
    P = A * 3
    S = A * A * math.sqrt(3)/4
    print_param(P, S)
elif(figure == '6'):
    A = int(input("Введите стороны a: "))
    B = int(input("Введите основание b: "))
    P = A + A + B
    S = B * math.sqrt(4 * A * A - B * B) / 4
    print_param(P, S)
elif(figure == '7'):
    A = int(input("Введите стороны a: "))
    H = int(input("Введите высоту h: "))
    P = A * 4
    S = A * H
    print_param(P, S)
elif(figure == '8'):
    A = int(input("Введите стороны a: "))
    N = int(input("Введите количество сторон n: "))
    P = A * N
    S = (N * A * A) /(math.tan(math.pi / N) * 4) 
    print_param(P, S)
else: print("Фигуры с таким номером нет")


