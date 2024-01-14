import operator
import string
 
# открываем файл в режиме чтения
book = open("article_eng.txt", "r", encoding='utf-8')
 
# чтение данных из файла
words = (book.read().split())
 
# закрываем исходный файл
book.close()
 
# словарь из букв английского алфавита со значениями 0
d = dict.fromkeys(string.ascii_lowercase, 0)
lettersoverall = 0
 
# проходим по словам файла
for word in words:
    # делим слово на символы
    chars = list(word)
    # проходим по каждому символу
    for char in chars:
        # проверка, является ли символ буквой
        if str(char).lower() in d:
            d[str(char).lower()] += 1
            lettersoverall += 1
 
# сортируем словарь по значениям
d = dict(sorted(d.items(), key=operator.itemgetter(1)))
# разворачиваем словарь
ans = dict(reversed(list(d.items())))
 
# открываем файл в режим записи
resultfile = open("article_eng_solve.txt", "w")
 
# записываем словарь в файл
for elem in ans:
    resultfile.write(str(elem) + ": " + str(ans[elem] / lettersoverall) + "\n")
resultfile.close()