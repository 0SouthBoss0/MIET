using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;

namespace ConsoleApp5
{
    // универсальный делегат
    delegate TKey KeySelector<TKey>(ResearchTeam rt);

    delegate void ResearchTeamsChangedHandler<TKey>(object source, ResearchTeamsChangedEventArgs<TKey>args);

    class ResearchTeamCollection<TKey>
    {
        private KeySelector<TKey> keyselector;
        public Dictionary<TKey, ResearchTeam> collection = new Dictionary<TKey, ResearchTeam>();

        public string collectionname { get; set; }
        public event ResearchTeamsChangedHandler<TKey> ResearchTeamsChanged;

        private void HandleEvent(object subject, EventArgs e)
        {
            var it = (PropertyChangedEventArgs)e;
            var mg = (ResearchTeam)subject;
            var key = mg.Regnumber;
            ResearchTeamsChanged?.Invoke(this, new ResearchTeamsChangedEventArgs<TKey>(collectionname, Revision.Property, "Topic", key));
        }

        public bool Replace(ResearchTeam rtold, ResearchTeam rtnew)
        {
            if (collection.ContainsValue(rtold))
            {
                foreach (KeyValuePair<TKey, ResearchTeam> rtpair in collection)
                {
                    if (rtpair.Value == rtold)
                    {

                        ResearchTeamsChanged?.Invoke(this, new ResearchTeamsChangedEventArgs<TKey>(collectionname, Revision.Replace, "", collection[rtpair.Key].Regnumber));
                        collection[rtpair.Key] = rtnew;

                        rtold.PropertyChanged -= HandleEvent;
                        rtnew.PropertyChanged += HandleEvent;
                        return true;
                    }
                }
            }
            return false;
        }

        public bool Remove(ResearchTeam rt)
        {
            if (collection.ContainsValue(rt))
            {
                foreach (KeyValuePair<TKey, ResearchTeam> rtpair in collection)
                {
                    if (rtpair.Value == rt)
                    {
                        ResearchTeamsChanged?.Invoke(this, new ResearchTeamsChangedEventArgs<TKey>(collectionname, Revision.Remove, "", collection[rtpair.Key].Regnumber));
                        collection.Remove(rtpair.Key);
                        rt.PropertyChanged -= HandleEvent;
                        return true;
                    }
                }
            }
            return false;
        }


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
                ResearchTeamsChanged?.Invoke(this, new ResearchTeamsChangedEventArgs<TKey>(collectionname, Revision.Property, "", resteam.Regnumber));
                collection.Add(keyselector(resteam), resteam);
                resteam.PropertyChanged += HandleEvent;
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
