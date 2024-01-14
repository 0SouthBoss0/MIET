using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp5
{
    class TeamsJournalEntry
    {
        public string collectionname { get; set; }
        public Revision reason { get; set; }
        public string property { get; set; }
        public int number { get; set; }


        public TeamsJournalEntry(string collectionname, Revision reason, string property, int number)
        {
            this.collectionname = collectionname;
            this.reason = reason;
            this.property = property;
            this.number = number;
        }

        public override string ToString()
        {
            return "Изменения в " + collectionname + "\nСобытие вызвано " + reason + "\nИзменения в свойстве " + property + "\nНомер регистрации " + number;
        }
    }
}
