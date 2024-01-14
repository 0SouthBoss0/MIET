import ipaddress


# сокращение IPv6
def shortipv6(ip):
    return str(ipaddress.ip_address(ip))


# проверка валидности IPv6
def validipv6(ip):
    try:
        addr = ipaddress.IPv6Address(ip)
    except ipaddress.AddressValueError:
        return False
    return True


# открываем файл в режиме чтения
ipfile = open("ip.log", "r")

# чтение данных из файла
arr = ipfile.read().splitlines()

# закрываем файл
ipfile.close()

# ввод пользователя
inputip = input("Введите Ваш IPv6: ")

# открываем файл в режим записи
resultfile = open("ip_solve.txt", "w")

if validipv6(inputip):
    # сравниваем введённый ip со всеми ip из файла
    for i in range(len(arr)):
        resultfile.write(str(shortipv6(inputip) == shortipv6(arr[i])) + "\n")
else:
    print("Неверно введён IPv6!")

# закрываем файл
resultfile.close()
