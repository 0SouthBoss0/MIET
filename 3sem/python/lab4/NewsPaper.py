import lab4.EconomicArticle
from Body import Body
from InterviewArticle import InterviewArticle
from EconomicArticle import EconomicArticle
from TaskChosenException import TaskChosenException
import pickle


def callMenu():
    print("\033[92mЗагрузить данные из файла: .............................1")
    print("Добавить новый объект: .................................2")
    print("Вывести информацию о объектах: .........................3")
    print("Сохранение и завершение сессии: ........................0\033[00m")


def checkValidInt(data: str, start: int, finish: int) -> int:
    try:
        validint = int(data)
        if validint < start or validint > finish:
            raise TaskChosenException
        return validint
    except ValueError:
        print("Введено не число!")
        return -1
        # пользовательское исключение
    except TaskChosenException:
        print("Такого пункта меню не существует!")
        return -1


items = []
status = 1
while status:
    callMenu()

    taskchosen = -1
    while taskchosen == -1:
        taskchosen = checkValidInt(input(), 0, 3)

    match taskchosen:
        # возможность восстанавливать данные из файла (бинарная запись)
        case 1:
            # обработка исключений при чтении файла.
            try:
                with open("database.dat", "rb") as file:
                    items = pickle.load(file)
            except FileNotFoundError:
                print("Файла не существует!")
            except Exception:
                print("Ошибка чтения файла!")

        # пользовательский ввод данных с клавиатуры
        case 2:
            print("Введите тип нового объекта: (1 - EconomicArticle, 2 - InterviewArticle)")

            articletype = -1
            while articletype == -1:
                articletype = checkValidInt(input(), 1, 2)

            print("Введите текст статьи:")
            text = input()
            print("Введите аннотацию статьи:")
            annot = input()
            match articletype:
                case 1:
                    items.append(EconomicArticle(Body(text, annot), len(items), []))
                case 2:
                    print("Введите автора статьи:")
                    author = input()
                    items.append(InterviewArticle(Body(text, annot), len(items), [], author))
        case 3:
            for i in range(len(items)):
                if isinstance(items[i], lab4.EconomicArticle.EconomicArticle) or isinstance(items[i], EconomicArticle):
                    print("ID:" + str(i) + " Economic Article")
                if isinstance(items[i], lab4.InterviewArticle.InterviewArticle) or isinstance(items[i],
                                                                                              InterviewArticle):
                    print("ID:" + str(i) + " Interview Article")

        # возможность сохранять данные в файл (бинарная запись)
        case 0:
            # обработка исключений при записи файла.
            try:
                with open("database.dat", "wb") as file:
                    pickle.dump(items, file)
                    status = 0
            except Exception:
                print("Ошибка записи файла!")
