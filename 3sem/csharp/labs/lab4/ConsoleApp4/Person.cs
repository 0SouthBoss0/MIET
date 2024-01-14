using System;

namespace ConsoleApp4
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

        // переопределение виртуального метода bool Equals
        public override bool Equals(Object obj)
        {
            if (obj == null)
            {
                return false;
            }

            // если объект не является объектом класса Person
            Person p = obj as Person;
            if (p as Object == null)
            {
                return false;
            }

            return (name == p.name) && (surname == p.surname) && (date == p.date);
        }

        // определение операции ==
        public static bool operator ==(Person obj1, Person obj2)
        {
            if (ReferenceEquals(obj1, obj2))
            {
                return true;
            }
            if ((((object)obj1) == null) || (((object)obj2) == null))
            {
                return false;
            }
            return false;
        }

        // определение операции !=
        public static bool operator !=(Person obj1, Person obj2)
        {
            return !(obj1 == (obj2));

        }

        // переопредение виртуального метода int GetHashCode()
        public override int GetHashCode()
        {
            return surname.GetHashCode() + name.GetHashCode() + date.GetHashCode();
        }

        // виртуальный метод object DeepCopy()
        public virtual object DeepCopy()
        {
            return new Person(name, surname, date);

        }
    }
}