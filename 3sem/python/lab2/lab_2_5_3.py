import os
import sys

# обработки ошибок ввода
try:
    left = int(input("Введите left: "))
    if left < 1 or left > 100:
        raise ValueError
except ValueError:
    print("Ошибка ввода!")
    sys.exit()

try:
    right = int(input("Введите right: "))
    if right < 1 or right > 100 or right < left:
        raise ValueError
except ValueError:
    print("Ошибка ввода!")
    sys.exit()

k = 0
# проходим по каждому файлу
for i in range(100):
    filename = "example/file" + str(i + 1)
    # проверяем вхождение размера файла в введённые границы
    if left <= (os.path.getsize(filename) // 1024) <= right:
        k += 1
print(k)
