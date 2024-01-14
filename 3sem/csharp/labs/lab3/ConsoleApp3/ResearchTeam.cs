using System;
using System.Collections;
using System.Collections.Generic;

namespace ConsoleApp3
{
    class ResearchTeam : Team, INameAndCopy, IEnumerable
    {
        string topic;
        TimeFrame timeframe;
        List <Person> members = new List<Person>();
        List<Paper> publications = new List<Paper>();

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
            set { topic = value; }
        }

        public TimeFrame Timeframe
        {
            get { return timeframe; }
            set { timeframe = value; }
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
        public override object DeepCopy()
        {
            ResearchTeam CopyTeam = new ResearchTeam(topic, organization, regnumber, timeframe);
            CopyTeam.members = members;
            CopyTeam.publications = publications;
            return CopyTeam;
        }

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