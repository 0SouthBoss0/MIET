class Comment():
    # конструктор класса
    def __init__(self, com: str, user: int) -> None:
        self._com = com
        self._user = user

    def getUser(self) -> int:
        return self._user

    def getCom(self) -> str:
        return self._com

    def setUser(self, user: str) -> None:
        self._user = user

    def setCom(self, com: str) -> None:
        self._com = com

    # свойства полей класса
    user = property(getUser, setUser)
    com = property(getCom, setCom)

    def __str__(self) -> str:
        return self.com + str(self.user)
