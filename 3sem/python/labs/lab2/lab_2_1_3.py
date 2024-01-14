import random


# генератор IPv6 из доступных символов
def generateIP():
    alpha = "0123456789abcdef"
    ip = ""
    for i in range(8):
        for j in range(4):
            ip += random.choice(alpha)
        ip += ":"
    return ip[:-1]


# открываем файл в режим записи
ipfile = open("ip.log", "w")
arr = []

for i in range(10000):
    while True:
        # создаем новый IP
        temp = generateIP()
        # проверка уникальности
        if temp not in arr:
            arr.append(generateIP())
            ipfile.write(temp + "\n")
            break

# закрываем файл
ipfile.close()
