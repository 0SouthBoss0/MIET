using System;
using System.Collections.Generic;

namespace ConsoleApp4
{
    class TeamsJournal
    {
        private List<TeamsJournalEntry> changes_list = new List<TeamsJournalEntry>();

        public void add_changes(object source, EventArgs args)
        {
            ResearchTeamsChangedEventArgs<string> researchargs = (ResearchTeamsChangedEventArgs<string>)args;
            changes_list.Add(new TeamsJournalEntry(researchargs.collectionname, researchargs.reason, researchargs.property, researchargs.number));
        }
        public override string ToString()
        {
            string result = "Журнал событий:";
            foreach (var elem in changes_list)
            {
                result += "\n"  + elem.ToString() + "\n";

            }
            return result;

        }
    }
}
