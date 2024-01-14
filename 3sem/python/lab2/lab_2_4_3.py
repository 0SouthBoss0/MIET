import os
import random

# создаем директорию example
os.mkdir("example")

for i in range(100):
    # создаем имя файла
    filename = "example/file" + str(i + 1)
    # создаем файл
    newfile = open(filename, "wb")
    # генерируем случайный размер файла в Кб
    file_size = 1024 * random.randint(1, 100)
    # устанавливаем размер файла
    newfile.write(os.urandom(file_size))
    newfile.close()
