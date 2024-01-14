using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using static System.Net.Mime.MediaTypeNames;

namespace ConsoleApp5
{
    [Serializable]
    class ResearchTeam : Team, INameAndCopy, IEnumerable, INotifyPropertyChanged
    {
        string topic;
        TimeFrame timeframe;
        List <Person> members = new List<Person>();
        List<Paper> publications = new List<Paper>();

        // создание полной копии объекта с использованием сериализации
        public new ResearchTeam DeepCopy()
        {
            MemoryStream stream = new MemoryStream();
            try
             {     
                BinaryFormatter converter = new BinaryFormatter();
                converter.Serialize(stream, this);
                stream.Position = 0;
                return (ResearchTeam) converter.Deserialize(stream);
             }
             catch
             {
                 Console.WriteLine("Ошибка сериализации!");
                 return new ResearchTeam();
             }
            finally
            {
                stream.Close();
            }
            
        }

        // сохранение данных объекта в файле с помощью сериализации
        public bool Save(string filename)  
        {
            try
            {
                BinaryFormatter binFormat = new BinaryFormatter();
                using (Stream fStream = new FileStream(filename, FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    binFormat.Serialize(fStream, this);
                    fStream.Close();
                }
                return true;
            }
            catch
            {
                Console.WriteLine("Ошибка сериализации");
                return false;
            }
        }

        // инициализация объекта данными из файла с помощью сериализации
        public bool Load(string filename)  
        {
            if (!File.Exists(filename)) {
                Console.WriteLine("Такого файла не существует!");
                return false;
            }
            try
            {
                BinaryFormatter formatter = new BinaryFormatter();
                using (Stream fStream = File.OpenRead(filename))
                {
                    ResearchTeam deserialized = (ResearchTeam)formatter.Deserialize(fStream);
                    topic = deserialized.topic;
                    timeframe = deserialized.timeframe;
                    members = deserialized.members.ToList();
                    publications = deserialized.publications.ToList();
                    organization = deserialized.organization;
                    regnumber = deserialized.regnumber;
                    fStream.Close();
                    return true;
                }
            }
            catch
            {
                Console.WriteLine("Ошибка десериализации");
                return false;
            }
        }
        
        // добавление новой публикации, данные для которой вводятся с консоли
        public bool AddFromConsole()
        {
            try
            {
                Console.WriteLine("Введите новую публикацию одной строкой формата: Название+Имя+Фамилия+Число+Месяц+Год");
                string[] words = Console.ReadLine().Split('+', StringSplitOptions.RemoveEmptyEntries);
                var consoleauthor = new Person(words[1], words[2], new DateTime());
                var consolepaper = new Paper(words[0], consoleauthor, new DateTime(Convert.ToInt32(words[5]), Convert.ToInt32(words[4]), Convert.ToInt32(words[3])));
                publications.Add(consolepaper);
                return true;
            }
            catch
            {
                Console.WriteLine("Ошибка ввода!");
                return false;
            }

        }

        // сохранение объекта в файле с помощью сериализации
        public static bool Save(string filename, ref ResearchTeam rt) //сохранение всего объекта в файл
        {
            try
            {
                BinaryFormatter binFormat = new BinaryFormatter();
                using (Stream fStream = new FileStream(filename, FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    binFormat.Serialize(fStream, rt);
                    fStream.Close();
                }
                return true;
            }
            catch
            {
                Console.WriteLine("Ошибка сериализации");
                return false;
            }
        }

        //  восстановления объекта из файла с помощью десериализации
        public static bool Load(string filename, ref ResearchTeam rt)
        {
            if (!File.Exists(filename))
            {
                Console.WriteLine("Такого файла не существует!");
                return false;
            }
            try
            {
                BinaryFormatter formatter = new BinaryFormatter();
                using (Stream fStream = File.OpenRead(filename))
                {
                    ResearchTeam deserialized = (ResearchTeam)formatter.Deserialize(fStream);
                    rt.topic = deserialized.topic;
                    rt.timeframe = deserialized.timeframe;
                    rt.members = deserialized.members.ToList();
                    rt.publications = deserialized.publications.ToList();
                    rt.organization = deserialized.organization;
                    rt.regnumber = deserialized.regnumber;
                    fStream.Close();
                    return true;
                }
            }
            catch
            {
                Console.WriteLine("Ошибка десериализации");
                return false;
            }
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
        public ResearchTeam(string topic, string organization, int regnumber, TimeFrame timeframe) : base(organization, regnumber)
        {
            this.topic = topic;
            this.timeframe = timeframe;
        }

        public ResearchTeam() : base()
        {
            topic = "Тема";
            timeframe = new TimeFrame();
        }

        public List<Paper> Publications
        {
            get { return publications; }
            set { publications = value; }
        }

        public List<Person> Members
        {
            get { return members; }
            set { members = value; }
        }

        public Team localTeam
        {
            get
            {
                return new Team(organization, regnumber);
            }
            set
            {
                this.organization = value.Organization;
                this.regnumber = value.Regnumber;
            }
        }

        public string Topic
        {
            get { return topic; }
            set {
                topic = value;
                OnPropertyChanged("topic");
            }
        }

        public TimeFrame Timeframe
        {
            get { return timeframe; }
            set {
                timeframe = value;
                OnPropertyChanged("timeframe");
            }
        }

        // публикация с самой поздней датой выхода
        public Paper LastPaper
        {
            get
            {
                if (publications.Count == 0)
                {
                    return null;
                }
                int maxindex = 0;
                DateTime lasttime = (publications[0] as Paper).publicityDate;
                
                for (int i = 0; i < publications.Count; i++)
                {
                    
                    if ((publications[i] as Paper).publicityDate > lasttime)
                    {
                        maxindex = i;
                        lasttime = (publications[i] as Paper).publicityDate;
                    }
                }
                
                return publications[maxindex] as Paper;
            }
        }

        // проверка совпадения продолжительности исследования индексатором булевского типа
        public bool this[TimeFrame timeFrame]
        {
            get
            {
                return timeFrame == this.timeframe;
            }
        }
        // метод для добавления элементов в список публикаций
        public void AddPapers(List<Paper> AdditionalPapers)
        {
            Publications.AddRange(AdditionalPapers);
        }

        // метод для добавления элементов в список участников проекта
        public void AddMembers(List<Person> AdditionalMembers)
        {
            Members.AddRange(AdditionalMembers);
        }

        // формирование строки со значениями всех полей класса, включая список публикаций и список участников проекта
        public override string ToString()
        {
            string temp = "Тема: " + topic + "\nОрганизация: " + organization + "\nНомер: " + regnumber + "\nСрок: " + timeframe.ToString() + "\n" + "Публикации: \n";
            for (int i = 0; i < publications.Count; i++)
            {
                temp += publications[i].ToString() + "\n";
            }

            temp += "Участники:\n";

            for (int i = 0; i < members.Count; i++)
            {
                temp += members[i].ToString() + "\n";
            }

            return temp;

        }

        // формирование строки со значениями всех полей класса без списка публикаций и списка участников проекта
        public virtual string ToShortString()
        {
            return "Тема: " + topic + "\nОрганизация: " + organization + "\nНомер: " + regnumber + "\nСрок: " + timeframe.ToString();
        }

        // перегруженная версия виртуального метода object DeepCopy()
        /*public override object DeepCopy()
        {
            ResearchTeam CopyTeam = new ResearchTeam(topic, organization, regnumber, timeframe);
            CopyTeam.members = members;
            CopyTeam.publications = publications;
            return CopyTeam;
        }*/

        // реализация интерфейса INameAndCopy
        public override string Name
        {
            get { return String.Format("Номер: {0}, Организация: {1}", regnumber, organization); }
            set => throw new NotImplementedException();
        }

        // итератор для последовательного перебора участников проекта, не имеющих публикаций
        public IEnumerable<Person> MembersWithoutPublications()
        {

            ArrayList emptyauthors = new ArrayList();
            bool flag;
            foreach (Person person in members)
            {
                flag = true;
                foreach (Paper paper in publications)
                {
                    if (paper.author == person)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    yield return person;
                }

            }

        }

        // итератор с параметром типа int для перебора публикаций, вышедших за последние n лет
        public IEnumerable<Paper> LastPapers(int years)
        {
            for (int i = 0; i < Publications.Count; i++)
            {
                if ((Publications[i] as Paper).publicityDate.Year >= DateTime.Now.Year - years)
                {
                    yield return Publications[i] as Paper;

                }
            }
        }

        public IEnumerator GetEnumerator()
        {
            return new ResearchTeamEnumerator(members, publications);
        }

        // итератор для последовательного перебора участников проекта, имеющих более одной публикации
        public IEnumerable<Person> OneOrMorePubs()
        {

            foreach (Person person in members)
            {
                int pubscount = 0;
                foreach (Paper paper in publications)
                {

                    if ((Person)paper.author == person)
                    {
                        pubscount += 1;
                    }
                }

                if (pubscount > 1)
                {
                    yield return person;
                }

            }


        }
        
        // метод для сортировки списка публикаций по дате выхода
        public void sortByPublicityDate()
        {
            publications.Sort();
        }

        // метод для сортировки списка публикаций по названию
        public void sortByTopic()
        {
            publications.Sort(new Paper());
        }

        // метод для сортировки списка публикаций по фамилии автора
        public void sortBySurname()
        {
            publications.Sort(new PaperSurname());
        }
    }
}