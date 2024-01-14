from typing import Generator
import random as rnd
from lab3.Body import Body
from lab3.Comment import Comment


class CommentGenerator:
    def commentGenerator(self, n: int) -> Generator[Comment, None, None]:
        for i in range(n):
            com = "Комментарий " + str(i + 1)
            yield Comment(com, rnd.randint(1, 100))

    def getGeneratedComments(self, n: int) -> [Comment]:
        localcomm = []
        gen = self.commentGenerator(n)
        for item in gen:
            localcomm.append(item)
        return localcomm
