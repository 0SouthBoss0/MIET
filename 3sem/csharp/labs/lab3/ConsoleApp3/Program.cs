using System;
using System.Collections.Generic;
using System.Reflection;

namespace ConsoleApp3
{
    class Program
    {

        public static void printTask(string message)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(message);
            Console.ForegroundColor = ConsoleColor.White;
        }

        static void Main(string[] args)
        {
            /*
             * Создание объектов ResearchTeam
             */

            ResearchTeam researchteam = new ResearchTeam("Исследование", "Организация 2", 15, TimeFrame.Year);

            Person person1 = new Person("Иван", "Петров", new DateTime(2000, 10, 5));
            Person person2 = new Person("Петр", "Александров", new DateTime(1995, 6, 25));
            Person person3 = new Person("Александр", "Иванов", new DateTime(2001, 2, 3));
            var members = new List<Person> { person1, person2, person3 };
            researchteam.AddMembers(members);

            Paper paper1 = new Paper("Первое исследование", person1, new DateTime(2023, 3, 30));
            Paper paper2 = new Paper("Второе исследование", person3, new DateTime(2014, 5, 16));
            Paper paper3 = new Paper("Третье исследование", person2, new DateTime(2022, 5, 16));
            var publications = new List<Paper> { paper1, paper2, paper3 };
            researchteam.AddPapers(publications);


            /*
             * Создать объект ResearchTeam и вызвать методы, выполняющие сортировку списка публикаций List<Paper> по разным критериям, 
             * после каждой сортировки вывести данные объекта.
             * Выполнить сортировку:
             * - по дате выхода публикации;
             * - по названию публикации;
             * - по фамилии автора. 
             */

            printTask("Сортировка по дате выхода публикации:");
            researchteam.sortByPublicityDate();
            foreach (Paper paper in researchteam.Publications)
                Console.WriteLine(paper);

            printTask("\nСортировка по названию публикации:");
            researchteam.sortByTopic() ;
            foreach (Paper paper in researchteam.Publications)
                Console.WriteLine(paper);

            printTask("\nСортировка по фамилии автора:");
            researchteam.sortBySurname();
            foreach (Paper paper in researchteam.Publications)
                Console.WriteLine(paper);

            /*
             *  Создать объект ResearchTeamCollection<string>. 
             *  Добавить в коллекцию несколько разных элементов ResearchTeam и вывести объект ResearchTeamCollection<string>.
             */

            ResearchTeamCollection<string> myrtcollection = new ResearchTeamCollection<string>(ResearchTeamCollection<string>.Define_Key);
            
            myrtcollection.addDefaults();
            myrtcollection.addResearchTeams(researchteam);
            printTask("\nОбъект ResearchTeamCollection<string>:");
            Console.WriteLine(myrtcollection.ToString());


            /*
             * Вызвать методы класса ResearchTeamCollection<string>, выполняющие операции с коллекцией-словарем Dictionary<TKey, ResearchTeam>,
             * после каждой операции вывести результат операции.
             * Выполнить:
             * - поиск даты последней по времени выхода публикации среди всех элементов коллекции;
             * - вызвать метод TimeFrameGroup для выбора объектов ResearchTeam с заданным значением продолжительности исследований;
             * - вызвать свойство класса, выполняющее группировку элементов коллекции по значениию продолжительности исследований,
             * вывести все группы элементов из списка. 
             */

            printTask("Публикации с продолжительностью Long:");
            foreach (var item in myrtcollection.TimeFrameGroup(TimeFrame.Long))
            {
                Console.WriteLine(item.Value.ToShortString());
            }


            printTask("\nГруппировка элементов коллекции по продолжительности:");
            foreach (var item in myrtcollection.GroupCollection)
            {
                Console.WriteLine(item.Key);
                foreach (var subitem in item)
                {
                    Console.WriteLine(subitem);
                }
            }

            /*
             * Создать объект типа TestCollection<Team, ResearchTeam>. 
             * Ввести число элементов в коллекциях и вызвать метод для поиска первого, центрального, последнего и элемента, не входящего в коллекции.
             * Вывести значения времени поиска для всех четырех случаев. 
             */

            int num = -1;
            Console.Write("\nВведите размер коллекции: ");
            while (!int.TryParse(Console.ReadLine(), out num) || num < 0)
            {
                Console.Write("Некорректный ввод. Повторите ввод: ");
            }

            TestCollections<Team, ResearchTeam> searchTest = new TestCollections<Team, ResearchTeam>(num, TestCollections<Team, ResearchTeam>.GenerateElement);

            searchTest.searchKeyList();
            searchTest.searchStrList();
            searchTest.searchTKeyDictionaryByKey();
            searchTest.searchStrDictionaryByKey();
            searchTest.searchTKeyDictionaryByValue();


        }
    }
}
