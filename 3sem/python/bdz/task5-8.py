import pandas as pd
from matplotlib import pyplot as plt
from sklearn.ensemble import RandomForestClassifier


def printTask(task):
    print("\n\033[95m" + task + "\033[0m")


def printSubTask(task):
    print("\033[94m" + task + "\033[0m")


def getReady(data):
    # заполнение возраста медианой
    data["Age"] = data['Age'].fillna(data['Age'].median())

    # заполнение тарифа медианой
    data["Fare"] = data['Fare'].fillna(data['Fare'].median())

    # заполнение каюты самой популярной каютой
    # print(data['Cabin'].value_counts(ascending=False))
    data['Cabin'] = data['Cabin'].fillna("B96")

    # заполнение порта самым популярным портом
    # print(data['Embarked'].value_counts(ascending=False))
    data['Embarked'] = data['Embarked'].fillna("S")

    # замена пола на число
    genders = {"male": 1, "female": 0}
    data["Sex"] = data["Sex"].apply(lambda s: genders.get(s))

    # замена порта на число
    embarkments = {"S": 1, "C": 2, "Q": 3}
    data["Embarked"] = data["Embarked"].apply(lambda e: embarkments.get(e))

    # подсчёт количества родственников на борту
    data["SibSp"] = data["Parch"] + data["SibSp"]

    # буква каюты
    letters = {"A": 1, "B": 2, "C": 3, "D": 4, "E": 5, "F": 6, "G": 7, "T": 8}
    data["Cabin"] = data["Cabin"].apply(lambda c: letters.get(c[0], -1))

    # очиcтка ненужных данных
    data.drop('Name', axis=1, inplace=True)
    data.drop('Ticket', axis=1, inplace=True)


data = pd.read_csv('train.csv')

printTask("Задание №5. Заполните все отсутствующие в train.csv значения медианой (по столбцу).")

printSubTask("Число отсутствующих значений в столбцах до заполнения:")
print(data.isnull().sum())
getReady(data)
printSubTask("Число отсутствующих значений в столбцах после заполнения:")
print(data.isnull().sum())

test_data = pd.read_csv("test.csv")
getReady(test_data)

expected_data = data['Survived']
rf = RandomForestClassifier(n_estimators=100)

data.drop('Survived', axis=1, inplace=True)
rf.fit(data, expected_data)

pred = rf.predict(test_data)

output = pd.DataFrame({'PassengerId': test_data.PassengerId, 'Survived': pred})
output.to_csv('submission.csv', index=False)

printTask("Задание №8 (+3 дополнительных балла). С помощью библиотеки matplotlib отобразите гистограмму зависимости возраста (в годах) от выживаемости.")
data = pd.read_csv('train.csv')
data[data['Survived'] == 1]['Age'].hist()
plt.title("Гистограмма выживших по возрасту")
plt.show()
