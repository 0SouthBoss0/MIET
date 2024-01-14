using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Reflection;

namespace ConsoleApp5
{
    class Program
    {
        static void printTask(string message)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(message);
            Console.ForegroundColor = ConsoleColor.White;

        }

        static void Main(string[] args)
        {
            /*
             * Создать объект типа T с непустым списком элементов, для которого предусмотрен ввод данных с консоли. 
             * Создать полную копию объекта с помощью метода, использующего сериализацию, и вывести исходный объект и его копию.
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

            printTask("Задание 1. Исходный объект:");
            Console.WriteLine(researchteam);

            printTask("Задание 1. Копия объекта:");
            Console.WriteLine(researchteam.DeepCopy());

            /*
             * Предложить пользователю ввести имя файла: 
             * - если файла с введенным именем нет, приложение должно сообщить об этом и создать файл; 
             * - если файл существует, вызвать метод Load(string filename) для инициализации объекта T данными из файла. 
            */

            printTask("Задание 2. Введите имя файла:");


            string filename = Console.ReadLine();
            
            var fi = new FileInfo(filename);
            if (fi.Exists)
            {
                researchteam.Load(filename);
                printTask("Задание 2. Файл загружен:");
                Console.WriteLine(researchteam);
            }
            else
            {
                printTask("Задание 2. Такого файла нет.");
                fi.Create().Close();
                printTask("Пустой файл был создан.\n");
            }

            /*
             *  Вывести объект
             */

            printTask("Задание 3. Вывести объект:");
            Console.WriteLine(researchteam);

            /*
             * Для этого же объекта T сначала вызвать метод AddFromConsole(), затем метод Save(string filename). 
             * Вывести объект T. 
            */

            printTask("Задание 4. Добавить из консоли:");
            if (researchteam.AddFromConsole())
            {
                printTask("Задание 4. Успешно добавлена новая публикация!");
            }
            
            researchteam.Save(filename);
            printTask("Вызов метода Save");

            printTask("Задание 4. Вывести объект:");
            Console.WriteLine(researchteam);
           
            /*
             * Вызвать последовательно:
             * - статический метод Load (string filename, T obj), передав как параметры ссылку на тот же самый объект T и введенное ранее имя файла; 
             * - метод AddFromConsole(); 
             * - статический метод Save (string filename, T obj). 
            */

            ResearchTeam.Load(filename, ref researchteam);
            printTask("Вызов статического метода Load");

            printTask("Задание 5. Добавить из консоли:");
            researchteam.AddFromConsole();

            ResearchTeam.Save(filename, ref researchteam);
            printTask("Вызов статического метода Save");

            /*
             * Вывести объект T.
             */

            printTask("Задание 6. Вывести объект:");
            Console.WriteLine(researchteam);

        }
    }
}
