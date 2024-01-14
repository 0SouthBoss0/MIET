using System;
using System.Collections;
using System.Collections.Generic;

namespace ConsoleApp5
{
    class ResearchTeamEnumerator : IEnumerator
    {

        public List<Person> members = new List<Person>();
        public List<Paper> publications = new List<Paper>();
        int position = 0;

        public ResearchTeamEnumerator(List<Person> members, List<Paper> publications)
        {
            this.members = new List<Person>(members);
            this.publications = new List<Paper>(publications);

        }

        public ResearchTeamEnumerator()
        {
            members = new List<Person>(0);
            publications = new List<Paper>(0);
        }

        public object Current
        {
            get
            {
                if (position == -1 || position >= members.Count + 1)
                    throw new IndexOutOfRangeException();
                return members[position - 1];
            }
        }

        public bool MoveNext()
        {
            for (int i = position + 1; i < members.Count + 1; i++)
            {

                foreach (Paper pub in publications)
                {
                    if ((Person)members[i - 1] == pub.author)
                    {

                        position = i;
                        return true;
                    }

                }
            }

            return false;

        }

        public void Reset()
        {
            position = 0;
        }
    }
}
