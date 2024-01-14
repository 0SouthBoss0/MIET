import pandas as pd


def printTask(task):
    print("\n\033[95m" + task + "\033[0m")


def printSubTask(task):
    print("\033[94m" + task + "\033[0m")


data = pd.read_csv('train.csv')

printTask("Задание №1. С помощью модуля pandas выведите статистику погибших/выживших отдельно для мужчин и женщин в каждом классе.")
print(data.groupby(["Sex", "Pclass"])['Survived'].value_counts())

printTask("Задание №2. С помощью модуля pandas выведите статистику по всем числовым полям, отдельно для мужчин и женщин")
printSubTask("Статистика для мужчин:")
print(data[data["Sex"] == "male"].describe(include='number'))
printSubTask("Статистика для женщин:")
print(data[data["Sex"] == "female"].describe(include='number'))

printTask("Задание №3. Определите, влияет ли порт посадки на выживаемость.")
printSubTask("Вероятность выжить в зависимости от порта посадки:")
print(data.groupby('Embarked')['Survived'].mean())

