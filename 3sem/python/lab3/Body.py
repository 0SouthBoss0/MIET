# тело статьи
class Body:
    # конструктор класса
    def __init__(self, text: str, annotation: str) -> None:
        self._text = text
        self._annotation = annotation

    # геттеры и сеттеры для полей класса
    def getText(self) -> str:
        return self._text

    def getAnnotation(self) -> str:
        return self._annotation

    def setText(self, text: str) -> None:
        if text == "":
            raise ValueError("Пустое содержание статьи!")
        self._text = text

    def setAnnotation(self, annotation: str) -> None:
        if annotation == "":
            raise ValueError("Пустое содержание аннотации!")
        self._annotation = annotation

    def __str__(self) -> str:
        return "\nАннотация: " + self.annotation + " \nСодержание: " + self.text


    # свойства полей класса
    text = property(getText, setText)
    annotation = property(getAnnotation, setAnnotation)
