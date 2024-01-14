using System;
using System.Collections;

namespace ConsoleApp2
{
    class ResearchTeamEnumerator : IEnumerator
    {

        public ArrayList members = new ArrayList();
        public ArrayList publications = new ArrayList();
        int position = 0;

        public ResearchTeamEnumerator(ArrayList members, ArrayList publications)
        {
            this.members = new ArrayList(members);
            this.publications = new ArrayList(publications);

        }

        public ResearchTeamEnumerator()
        {
            members = new ArrayList(0);
            publications = new ArrayList(0);
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
