using System;

namespace ConsoleApp1
{
    class ResearchTeam
    {
        string topic;
        string organization;
        int regnumber;
        TimeFrame timeframe;
        Paper[] papers;

        public ResearchTeam(string topic, string organization, int regnumber,
                            TimeFrame timeframe, Paper[] papers)
        {
            this.topic = topic;
            this.organization = organization;
            this.regnumber = regnumber;
            this.timeframe = timeframe;
            this.papers = papers;
        }

        public ResearchTeam()
        {
            topic = "Тема";
            organization = "Организация";
            regnumber = 0;
            timeframe = TimeFrame.Long;
            papers = new Paper[0];
        }

        public string Topic
        {
            get { return topic; }
            set { topic = value; }
        }

        public string Organization
        {
            get { return organization; }
            set { organization = value; }
        }

        public int Regnumber
        {
            get { return regnumber; }
            set { regnumber = value; }
        }
        public TimeFrame Timeframe
        {
            get { return timeframe; }
            set { timeframe = value; }
        }

        public Paper[] Paper
        {
            get
            {
                return papers;
            }
            set { papers = value; }
        }

        // свойство, которое возвращает ссылку на публикацию с самой поздней датой выхода
        public ref Paper lastPaper(ref Paper ifNotFound)
        {
            if (papers.Length == 0)
            {
                return ref ifNotFound;
            }

            Paper temp;
            for (int i = 0; i < papers.Length; i++)
            {
                for (int j = i + 1; j < papers.Length; j++)
                {
                    if (papers[i].publicityDate > papers[j].publicityDate)
                    {
                        temp = papers[i];
                        papers[i] = papers[j];
                        papers[j] = temp;
                    }
                }
            }

            return ref papers[papers.Length - 1];
        }

        // проверка совпадения продолжительности исследования индексатором булевского типа
        public bool this[TimeFrame timeFrame]
        {
            get
            {
                return timeFrame == this.timeframe;
            }
        }

        // добавление элементов в список публикаций
        public void addPapers(params Paper[] new_papers)
        {
            int size = papers.Length;
            Array.Resize<Paper>(ref papers, size + new_papers.Length);
            for (int i = 0; i < new_papers.Length; i++)
                papers[size + i] = new_papers[i];
        }

        public override string ToString()
        {
            string temp = "Тема: " + topic + "\nОрганизация: " + organization + "\nНомер: " + regnumber + "\nСрок: " + timeframe.ToString() + "\n";
            for (int i = 0; i < papers.Length; i++)
            {
                temp += papers[i].ToString() + "\n";
            }
            return temp;
        }
        public virtual string ToShortString()
        {
            return "Тема: " + topic + "\nОрганизация: " + organization + "\nНомер: " + regnumber + "\nСрок: " + timeframe.ToString();
        }
    }
}
