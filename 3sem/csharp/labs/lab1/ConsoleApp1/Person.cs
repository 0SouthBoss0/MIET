using System;

namespace ConsoleApp1
{
    class Person
    {
        string name;
        string surname;
        DateTime date;

        public Person(string name, string surname, DateTime date)
        {
            this.name = name;
            this.surname = surname;
            this.date = date;
        }

        public Person()
        {
            name = "Имя";
            surname = "Фамилия";
            date = new DateTime();
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string Surname
        {
            get { return surname; }
            set { surname = value; }
        }

        public DateTime Date
        {
            get { return date; }
            set { date = value; }
        }

        public int birthYear
        {
            get { return date.Year; }
            set
            {
                DateTime newdate = new DateTime(value, date.Month, date.Day);
                date = newdate;
            }
        }

        public override string ToString()
        {
            return name + ", " + surname + ", " + date.ToString("d");
        }

        public virtual string ToShortString()
        {
            return name + ", " + surname;
        }
    }
}
