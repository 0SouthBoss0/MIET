using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Reflection;

namespace ConsoleApp4
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
             *  Создать две коллекции ResearchTeamCollection<string>.
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

            ResearchTeamCollection<string> myrtcollection = new ResearchTeamCollection<string>(ResearchTeamCollection<string>.Define_Key);

            myrtcollection.addDefaults();
            myrtcollection.addResearchTeams(researchteam);

            ResearchTeamCollection<string> myrtcollection2 = new ResearchTeamCollection<string>(ResearchTeamCollection<string>.Define_Key);
            myrtcollection2.addDefaults();


            /*
             *  Создать объект TeamsJournal, подписать его на события ResearchTeamsChanged из обоих объектов ResearchTeamCollection<string>.
             */

            TeamsJournal teamsjournal = new TeamsJournal();
            myrtcollection.ResearchTeamsChanged += teamsjournal.add_changes;
            myrtcollection2.ResearchTeamsChanged += teamsjournal.add_changes;

            /*
             *  Внести изменения в коллекции ResearchTeamCollection<string>
             *  - добавить элементы в коллекции;
             *  - изменить значения разных свойств элементов, входящих в коллекцию;
             *  - удалить элемент из коллекции;
             *  - изменить данные в удаленном элементе;
             *  - заменить один из элементов коллекции;
             *  - изменить данные в элементе, который был удален из коллекции при замене элемента. 
             */

            myrtcollection.collectionname = "Коллекция 1";
            myrtcollection2.collectionname = "Коллекция 2";

            // добавить элементы в коллекции
            ResearchTeam newrt = new ResearchTeam("Новое исследование", "Организация 25", 7, TimeFrame.Year);
            myrtcollection.addResearchTeams(newrt);
            myrtcollection2.addResearchTeams(new ResearchTeam("Новое изучение", "Организация 52", 97, TimeFrame.TwoYears));

            // изменить значения разных свойств элементов, входящих в коллекцию  
            myrtcollection.collection[researchteam.Regnumber.ToString()].Topic = "Изменённая тема";

            // удалить элемент из коллекции
            myrtcollection.Remove(researchteam);

            // изменить данные в удаленном элементе
            researchteam.Topic = "Дважды изменённая тема";

            // заменить один из элементов коллекции
            myrtcollection.Replace(newrt, new ResearchTeam("Новое изучение", "Организация 52", 97, TimeFrame.TwoYears));

            // изменить данные в элементе, который был удален из коллекции при замене элемента
            newrt.Topic = "Тема";

            /*
             *  Вывести данные объекта TeamsJournal. 
             */
            Console.WriteLine(teamsjournal);
        }
    }
}
