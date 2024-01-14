from Article import Article
from Body import Body


class EconomicArticle(Article):
    # конструктор класса
    def __init__(self, body: Body, id: int, comments: []) -> None:
        super().__init__(body, id, comments)
