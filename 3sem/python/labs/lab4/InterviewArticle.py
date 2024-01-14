from Article import Article
from Body import Body


class InterviewArticle(Article):
    # конструктор класса
    def __init__(self, body: Body, id: int, comments: [], person: str) -> None:
        super().__init__(body, id, comments)
        self._person = person

    # геттеры и сеттеры для полей класса
    def getPerson(self) -> str:
        return self._person

    def setPerson(self, person) -> None:
        self._person = person

    def addFavourite(self, note=None) -> None:
        if note != None:
            print("Интервью с заметкой успешно добавлены в избранные!")
        else:
            print("Интервью успешно добавлено в избранное!")

    def __str__(self) -> str:
        return "Интервью." + str(self.body) + "\nПро человека: " + self.person + " \nID: " + str(self.id) + "\nКомментарии:\n" + self.listToString(self.comments)

    # свойства полей класса
    person = property(getPerson, setPerson)
