using System;

namespace ConsoleApp1
{
    using System.Diagnostics;

    enum TimeFrame { Year, TwoYears, Long }

    class Program
    {
        static void Main(string[] args)
        {

            /*
             * Создать один объект типа ResearchTeam, преобразовать данные в текстовый вид с помощью метода ToShortString() и вывести данные.
            */

            ResearchTeam researchTeam = new ResearchTeam();
            Console.WriteLine(researchTeam.ToShortString() + "\n");

            /*
             * Вывести значения индексатора для значений индекса TimeFrame.Year, TimeFrame.TwoYears, TimeFrame.Long
            */

            Console.WriteLine(researchTeam[TimeFrame.Year]);
            Console.WriteLine(researchTeam[TimeFrame.TwoYears]);
            Console.WriteLine(researchTeam[TimeFrame.Long] + "\n");

            /*
             * Присвоить значения всем определенным в типе ResearchTeam свойствам, преобразовать данные в текстовый вид с помощью метода ToString() и вывести данные.
            */

            Person person = new Person("Иван", "Иванов", new DateTime(2000, 5, 6));
            Person person1 = new Person("Петр", "Петров", new DateTime(1900, 1, 8));
            Paper[] papers = new Paper[3];
            papers[0] = new Paper("Проблематика", person, new DateTime(2000, 5, 6));
            papers[1] = new Paper("Изучение", person1, new DateTime(2001, 5, 6));
            papers[2] = new Paper("Моделирование", person, new DateTime(2200, 6, 6));

            researchTeam.Topic = "Исследование";
            researchTeam.Organization = "МИЭТ";
            researchTeam.Regnumber = 8221694;
            researchTeam.Timeframe = TimeFrame.Year;
            researchTeam.Paper = papers;

            Console.WriteLine(researchTeam.ToString() + "\n");

            /*
             * С помощью метода AddPapers (params Paper[]) добавить элементы в список публикаций и вывести данные объекта ResearchTeam
            */

            Person add_person = new Person("Редактор", "Редакторович", new DateTime(1991, 12, 26));
            Paper[] additions = new Paper[2];
            additions[0] = new Paper("Правки. I часть", add_person, new DateTime(1999, 12, 30));
            additions[1] = new Paper("Правки. II часть", add_person, new DateTime(1999, 12, 31));
            researchTeam.addPapers(additions);

            Console.WriteLine(researchTeam.ToString() + "\n");

            /*
            * Вывести значение свойства, которое возвращает ссылку на публикацию с самой поздней датой выхода;
           */

            Paper ifNotFound = null;
            Console.WriteLine(researchTeam.lastPaper(ref ifNotFound) + "\n");

            /*
            * Сравнить время выполнения операций с элементами одномерного, двумерного прямоугольного и двумерного ступенчатого массивов с одинаковым числом элементов типа Paper.
           */

            Console.WriteLine("Введите число столбцов и строк в формате {строка} {столбец}: ");
            string input = Console.ReadLine();

            string[] matrix_size = input.Split(" ");

            int nrow = int.Parse(matrix_size[0]);
            int ncol = int.Parse(matrix_size[1]);

            // создание одномерного массива
            ResearchTeam[] odnomer = new ResearchTeam[nrow * ncol];
            for (int i = 0; i < nrow * ncol; i++)
                odnomer[i] = new ResearchTeam();

            // создание двумерного массива
            ResearchTeam[,] dvumer = new ResearchTeam[nrow, ncol];
            for (int i = 0; i < nrow; i++)
                for (int j = 0; j < ncol; j++)
                    dvumer[i, j] = new ResearchTeam();

            // создание ступенчатого массива
            int k = 0;
            ResearchTeam[,] dvumer_stupen = new ResearchTeam[nrow + ncol, nrow + ncol];
            for (int i = 0; i < nrow + ncol; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    dvumer_stupen[i, j] = new ResearchTeam();
                    k++;
                    if (k == nrow * ncol)
                        break;
                }
                if (k == nrow * ncol)
                    break;
            }

            Stopwatch sw = new Stopwatch();

            sw = Stopwatch.StartNew();
            for (int i = 0; i < nrow * ncol; i++)
            {
                odnomer[i].Organization = "МИЭТ";
                odnomer[i].Regnumber = 8221694;
            }
            sw.Stop();
            Console.WriteLine("Одномерный массив:" + sw.Elapsed.ToString());

            sw = Stopwatch.StartNew();
            for (int i = 0; i < nrow; i++)
            {
                for (int j = 0; j < ncol; j++)
                {
                    dvumer[i, j].Organization = "МИЭТ";
                    dvumer[i, j].Regnumber = 8221694;
                }

            }
            sw.Stop();
            Console.WriteLine("Двумерный массив:" + sw.Elapsed.ToString());

            k = 0;
            sw = Stopwatch.StartNew();
            for (int i = 0; i < nrow + ncol; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    dvumer_stupen[i, j].Organization = "МИЭТ";
                    dvumer_stupen[i, j].Regnumber = 8221694;
                    k++;
                    if (k == nrow * ncol)
                        break;
                }
                if (k == nrow * ncol)
                    break;
            }

            sw.Stop();
            Console.WriteLine("Двумерный ступенчатый массив: " + sw.Elapsed.ToString());
        }
    }
}