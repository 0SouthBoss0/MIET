from lab4.BadWordException import BadWordException
from lab4.Body import Body
from lab4.CommentGenerator import CommentGenerator
from lab4.EconomicArticle import EconomicArticle
from lab4.InterviewArticle import InterviewArticle
import pytest


class Tests:
    @pytest.fixture(scope="module")
    def ecomonicArticle(self):
        body = Body("Пример содержания статьи", "Пример аннотации к статье")
        commentgenerator = CommentGenerator()
        ecominic = EconomicArticle(body, 2, [])
        ecominic.comments = commentgenerator.getGeneratedComments(5)
        return ecominic

    @pytest.fixture(scope="module")
    def interviewArticle(self):
        body = Body("Пример содержания статьи", "Пример аннотации к статье")
        commentgenerator = CommentGenerator()
        interview = InterviewArticle(body, 1, [], "Известный человек")
        interview.comments = commentgenerator.getGeneratedComments(3)
        return interview

    def test_getter(self, ecomonicArticle):
        assert ecomonicArticle.id == ecomonicArticle.getID()

    def test_equals(self, interviewArticle):
        interview2 = InterviewArticle(interviewArticle.body, interviewArticle.id, interviewArticle.comments,
                                      interviewArticle.person)
        assert interviewArticle == interview2

    def test_notEquals(self, ecomonicArticle, interviewArticle):
        assert ecomonicArticle != interviewArticle

    def test_lencomments(self, ecomonicArticle):
        assert len(ecomonicArticle.getComments()) == 5

    def test_BadComment(self, interviewArticle):
        with pytest.raises(BadWordException):
            interviewArticle.setComments(["badword"])
