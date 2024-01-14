using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp3
{
    // универсальный делегат
    delegate TKey KeySelector<TKey>(ResearchTeam rt);

    class ResearchTeamCollection<TKey>
    {
        private KeySelector<TKey> keyselector;
        private Dictionary<TKey, ResearchTeam> collection = new Dictionary<TKey, ResearchTeam>();
        
        public ResearchTeamCollection(KeySelector<TKey> keyselector)
        {
            collection = new Dictionary<TKey, ResearchTeam>();
            this.keyselector = keyselector;

        }
        public void addDefaults()
        {
            ResearchTeam researchteam2 = new ResearchTeam("Изучение", "Организация 5", 17, TimeFrame.Long);

            Person person4 = new Person("Евгений", "Дмитров", new DateTime(1954, 1, 1));
            Person person5 = new Person("Дмитрий", "Александров", new DateTime(2003, 8, 14));
            Person person6 = new Person("Александр", "Евгеньев", new DateTime(2001, 2, 3));
            var members2 = new List<Person> { person4, person5, person6 };
            researchteam2.AddMembers(members2);

            Paper paper4 = new Paper("Первое изучение", person6, new DateTime(1997, 3, 30));
            Paper paper5 = new Paper("Второе изучение", person5, new DateTime(2003, 6, 16));
            Paper paper6 = new Paper("Третье изучение", person5, new DateTime(1999, 5, 14));
            var publications2 = new List<Paper> { paper4, paper5, paper6 };
            researchteam2.AddPapers(publications2);

            collection.Add(keyselector(researchteam2), researchteam2);

        }

        public void addResearchTeams(params ResearchTeam[] researchteams)
        {
            foreach (var resteam in researchteams)
            {
                collection.Add(keyselector(resteam), resteam);
            }
        }

        public override string ToString()
        {
            string str = "ResearchTeams in collection:\n";
            foreach (var rt in collection.Values)
            {
                str += "\n" + rt.ToString();
            }

            return str;
        }

        public virtual string ToShortString()
        {
            string str = "ResearchTeams in collection:\n";
            foreach (var rt in collection.Values)
            {
                str += rt.ToShortString() + "\n";
            }
            return str;
        }

        public static string Define_Key(ResearchTeam rt)
        {
            return rt.Regnumber.ToString();
        }

        // свойство, возвращающее дату последней по времени выхода публикации среди всех элементов коллекции
        public DateTime DateOfLastPaper
        {
            get
            {
                if (collection.Values.Min(x => x.Publications.Count) > 0)
                {
                    return collection.Values.Max(x => x.LastPaper.publicityDate);
                }
                return new DateTime(1970, 1, 1);
            }
        }

        // метод, возвращающий подмножество элементов коллекции со значением продолжительности исследований, которое передается как параметр
        public IEnumerable<KeyValuePair<TKey, ResearchTeam>> TimeFrameGroup(TimeFrame value)
        {
            return collection.Where(item => item.Value.Timeframe == value);
        }

        // свойство, выполняющее группировку элементов коллекции в зависимости от продолжительности исследований
        public IEnumerable<IGrouping<TimeFrame, KeyValuePair<TKey, ResearchTeam>>> GroupCollection
        {
            get
            {
                return collection.GroupBy(item => item.Value.Timeframe);
            }
        }
    }
}
