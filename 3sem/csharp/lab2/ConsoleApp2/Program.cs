using System;

namespace ConsoleApp2
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
             * Создать два объекта типа Team с совпадающими данными и проверить, что ссылки на объекты не равны, а объекты равны, вывести значения хэш-кодов для объектов
             */

            Team team1 = new Team("Организация 1", 9);
            Team team2 = new Team("Организация 1", 9);

            Console.WriteLine("Равенство ссылок:");
            Console.WriteLine((object) team1 == (object)team2);
            Console.WriteLine("Равенство объектов:");
            Console.WriteLine(team1.Equals(team2));
            Console.WriteLine("Хэши объектов:");
            Console.WriteLine(string.Format("team1: {0}, team2: {1}\n", team1.GetHashCode(), team2.GetHashCode()));

            /*
             * В блоке try/catch присвоить свойству с номером регистрации некорректное значение, в обработчике исключения вывести сообщение, переданное через объект-исключение
             */

            Console.WriteLine("Присвоение некорректного значения:");
            try
            {
                team1.Regnumber = -1;
            }
            catch (NegativeRegNumber ex)
            {
                Console.WriteLine(ex.Message);
            }

            /*
             * Создать объект типа ResearchTeam, добавить элементы в список публикаций и список участников проекта и вывести данные объекта ResearchTeam
             */

            ResearchTeam researchteam = new ResearchTeam("Исследование", "Организация 2", 15, TimeFrame.Year);

            Person person1 = new Person("Иван", "Иванов", new DateTime(2000, 10, 5));
            Person person2 = new Person("Петр", "Петров", new DateTime(1995, 6, 25));
            Person person3 = new Person("Александр", "Александров", new DateTime(2001, 2, 3));

            Person[] members = { person1, person2, person3 };
            researchteam.AddMembers(members);

            Paper paper1 = new Paper("Исследование 1", person1, new DateTime(2023, 3, 30));
            Paper paper2 = new Paper("Исследование 2", person3, new DateTime(2014, 5, 16));
            Paper paper3 = new Paper("Исследование 2", person3, new DateTime(2022, 5, 16));

            Paper[] publications = { paper1, paper2, paper3 };
            researchteam.AddPapers(publications);

            Console.WriteLine("\n" + researchteam.ToString());

            /*
             * Вывести значение свойства Team для объекта типа ResearchTeam.
             */

            Console.WriteLine(researchteam.localTeam + "\n");

            /*
             * С помощью метода DeepCopy() создать полную копию объекта ResearchTeam. 
             * Изменить данные в исходном объекте ResearchTeam и вывести копию и исходный объект, полная копия исходного объекта должна остаться без изменений.
             */

            ResearchTeam researchteam2 = (ResearchTeam)researchteam.DeepCopy();
            Console.WriteLine("Равенство копий:");
            Console.WriteLine(researchteam == researchteam2);
            researchteam.Organization = "Организация 3";
            Console.WriteLine("Равенство копий после изменения:");
            Console.WriteLine(researchteam == researchteam2);
            Console.WriteLine();

            /*
            * С помощью оператора foreach для итератора, определенного в классе ResearchTeam, вывести список участников проекта, которые не имеют публикаций.
            */


            Console.WriteLine("Не имеют публикаций:");
            foreach (Person person in researchteam.MembersWithoutPublications())
            {
                Console.WriteLine(person);
            }

            /*
            * С помощью оператора foreach для итератора с параметром, определенного в классе ResearchTeam, вывести список всех публикаций, вышедших за последние два года.
            */

            Console.WriteLine("\nПубликации за последние 2 года:");
            foreach (Paper paper in researchteam.LastPapers(2))
            {
                Console.WriteLine(paper);
            }

            /*
            * С помощью оператора foreach для объекта типа ResearchTeam вывести список участников проекта, у которых есть публикации.
            */

            Console.WriteLine("\nУчастники у которых есть публикации:");
            foreach (Person person in researchteam)
            {
                Console.WriteLine(person);
            }

            /*
            * С помощью оператора foreach для объекта типа ResearchTeam вывести список участников проекта, у которых более одной публикации.
            */

            Console.WriteLine("\nУчастники у которых есть более одной публикации:");
            foreach (Person person in researchteam.OneOrMorePubs())
            {
                Console.WriteLine(person);
            }

            /*
            * С помощью оператора foreach для итератора с параметром, определенного в классе ResearchTeam, вывести список всех публикаций, вышедших за последний год.
            */

            Console.WriteLine("\nПубликации за последний год:");
            foreach (Paper paper in researchteam.LastPapers(1))
            {
                Console.WriteLine(paper);
            }
        }
    }
}
