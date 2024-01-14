from lab3.Article import Article
from lab3.Body import Body
from lab3.Comment import Comment
from lab3.CommentGenerator import CommentGenerator
from lab3.InterviewArticle import InterviewArticle
from lab3.EconomicArticle import EconomicArticle

body = Body("Пример содержания статьи", "Пример аннотации к статье")
commentgenerator = CommentGenerator()

interview = InterviewArticle(body, 1, [], "Известный человек")
ecominic = EconomicArticle(body, 2, [])

interview.comments = commentgenerator.getGeneratedComments(3)
ecominic.comments = commentgenerator.getGeneratedComments(5)

print(interview)
print(ecominic)

# демонстрация перегрузки и переопределения метода
interview.addFavourite()
interview.addFavourite("заметка")

# вызов не переопределенного метода
ecominic.addFavourite()

# демонстрация перегрузки оператора ==
print(interview == ecominic)
print(interview == interview)

print("\nID: ", ecominic.getID(), "\n")

# демонстрация работы генератора
for item in (commentgenerator.commentGenerator(5)):
    print(item)
