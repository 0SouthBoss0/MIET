import csv

arr = []

# открываем csv файл в режиме чтения
with open("orders.csv", "r", newline="", encoding="UTF8", errors='ignore') as file:
    reader = csv.reader(file, delimiter=";")
    # записываем кортежи с данными в массив
    for row in reader:
        arr.append((row[0], row[1], row[2]))
print("Данные из файла:\n", arr)

clients = {}
for i in range(1, len(arr)):
    if arr[i][0] not in clients:
        # создание нового клиента с покупкой
        clients[arr[i][0]] = [(arr[i][1], arr[i][2])]
    else:
        # добавление покупки к существующему клиенту
        clients[arr[i][0]].append((arr[i][1], arr[i][2]))
print("\nБаза клиентов:\n", clients)

answer = [("ID Клиента", "Общая сумма", "Любимый товар")]

# проходим по каждому клиенту
for item in clients.items():
    # вычисление суммы всех покупок клиента
    totalsum = 0
    for j in range(len(item[1])):
        totalsum += float(item[1][j][1])

    # проверка на целое число
    if totalsum % 1 == 0:
        totalsum = int(totalsum)
    # округление до 2 знаков после запятой
    else:
        totalsum = round(totalsum, 2)

    # вычисление всех товаров клиента
    shoppinglist = []
    for j in range(len(item[1])):
        shoppinglist.append(item[1][j][0])
    bestitem = max(set(shoppinglist), key=shoppinglist.count)

    answer.append((item[0], totalsum, bestitem))
print("\nРезультат аналитики: \n", answer)

# записываем в csv файл
with open("analytics.csv", "w", newline="", encoding="UTF8", errors='ignore') as file:
    writer = csv.writer(file, delimiter=";")
    writer.writerows(answer)
