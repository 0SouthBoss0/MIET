def callError():
    print("Ошибка ввода")
    quit()


n = 0
stroka = ""

# обработки ошибок ввода
try:
    n = int(input("Введите n:\n"))
except ValueError:
    callError()

print("Введите n строк формата {ряд} {место} {стоимость_билета}:")

movie = {}
pricechange = {}

for i in range(n):
    try:
        stroka = list(map(int, input().split()))
    except ValueError:
        callError()

    seat = (stroka[0], stroka[1])
    price = stroka[2]

    # сведения о цене билета уже существуют
    if seat in movie:
        # если есть изменение цены
        if movie[seat] != price:
            pricechange[seat] += 1
    else:
        pricechange[seat] = 1

    movie[seat] = price
print(pricechange)
