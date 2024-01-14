import pandas as pd


def printTask(task):
    print("\n\033[95m" + task + "\033[0m")


def printSubTask(task):
    print("\033[94m" + task + "\033[0m")


def getSurnames(fullname):
    f = fullname.str.split(',').str[0]
    return f


def getNames(fullname):
    first = fullname.str.extract(r"Mrs\.\s+[^(]*\((\w+)", expand=False)
    first.loc[first.isna()] = fullname.str.extract(r"\.\s+(\w+)", expand=False)
    return first


data = pd.read_csv('train.csv')

printTask("Задание №4. Выведите топ 10 популярных имён. Выведите топ 10 популярных фамилий.")
surnames = getSurnames(data["Name"])
names = getNames(data["Name"])

printSubTask("Топ 10 популярных имён")
print(names.value_counts()[:10].index.tolist())

printSubTask("Топ 10 популярных фамилий")
print(surnames.value_counts()[:10].index.tolist())

