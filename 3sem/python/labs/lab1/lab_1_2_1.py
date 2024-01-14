def callError():
    print("Ошибка ввода")
    quit()


n = -1
arr = []

# обработки ошибок ввода
try:
    n = int(input("Введите n:\n"))
except ValueError:
    callError()

try:
    arr = list(map(int, input("Введите n положительных чисел через пробел:\n").split()))
except ValueError:
    callError()

if len(arr) != n:
    callError()

print(arr)
k = 0

# выполняем итерации, пока в списке есть нули
while arr.count(0) != n:
    i = 0
    start = i

    # начало итерации
    while i < n:
        # выбираем максимальный отрезок, не содержащий нули
        if arr[i] == 0:
            if start != i:
                k += 1
                # уменьшаем элементы на единицу
                for j in range(start, i):
                    arr[j] -= 1
                print(arr)
            start = i + 1
        i += 1
    # проверяем величину конечного отрезка
    if start != i:
        k += 1
        for j in range(start, i):
            arr[j] -= 1
        print(arr)

print("Ответ:", k)
