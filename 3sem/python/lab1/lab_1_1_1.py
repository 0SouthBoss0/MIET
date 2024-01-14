s = input("Введите строку:\n")
x = input("Введите вирус:\n")

# проходим пока вирус входит в строку
while x.lower() in s.lower():
    s_arr = list(s)
    x_arr = list(x)
    # проходим до совпадения с первым символом вируса
    for i in range(len(s_arr) - len(x_arr) + 1):
        if s_arr[i].lower() == x_arr[0].lower():
            # сравниваем последующие символы
            for j in range(len(x_arr)):
                if s_arr[i + j].lower() != x_arr[j].lower():
                    break
            # все символы совпадают
            else:
                for j in range(len(x_arr)):
                    s_arr[i + j] = ""
    s = "".join(s_arr)

print("Строка без вируса:", s)
