from Body import Body
from Comment import Comment
from lab4.BadWordException import BadWordException


class Article:
    # конструктор класса
    def __init__(self, body: Body, id: int, comments: [Comment]):
        self._body = body
        self._id = id
        self._comments = comments

    # геттеры и сеттеры для полей класса
    def getBody(self) -> Body:
        return self._body

    def getID(self) -> int:
        return self._id

    def getComments(self) -> []:
        return self._comments

    def setBody(self, body: Body) -> None:
        self._body = body

    def setID(self, id: int) -> None:
        self._id = id

    def setComments(self, comments: Comment) -> None:
        for comment in comments:
            if comment == "badword":
                raise BadWordException

        self._comments = comments

    # свойства полей класса
    body = property(getBody, setBody)
    id = property(getID, setID)
    comments = property(getComments, setComments)

    def addFavourite(self) -> None:
        print("Статья успешно добавлена в избранные!")

    def __eq__(self, other) -> bool:
        return self._body == other._body and self._id == other._id and self._comments == other._comments

    def listToString(self, arr: [Comment]) -> str:
        s = ""
        for i in range(len(arr)):
            s += arr[i].com + str(arr[i].user) + "\n"
        return s

    def __str__(self) -> str:
        return "Статья. " + str(self.body) + "\nID: " + str(self.id) + "\nКомментарии:\n" + self.listToString(
            self.comments)
