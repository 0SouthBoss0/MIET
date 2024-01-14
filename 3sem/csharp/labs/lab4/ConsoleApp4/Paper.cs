using System;
using System.Collections.Generic;
using System.Xml.Linq;

namespace ConsoleApp4
{
    class Paper: IComparable<Paper>, IComparer<Paper>
    {
        public string title;
        public Person author;
        public DateTime publicityDate;

        public Paper(string title, Person author, DateTime publicityDate)
        {
            this.title = title;
            this.author = author;
            this.publicityDate = publicityDate;
        }

        public Paper()
        {
            title = "Название";
            author = new Person();
            publicityDate = new DateTime();
        }

        public override string ToString()
        {
            return title + ": " + author.ToShortString() + ", " + publicityDate.ToString("d");
        }

        // Реализация интерфейса IComparable для сравнения объектов типа Paper по дате выхода публикации
        public int CompareTo(Paper? other)
        {
            if (other is null) throw new ArgumentException("Некорректное значение параметра");
            return this.publicityDate.CompareTo(other.publicityDate);
        }

        //  Реализация интерфейса IComparer<Paper> для сравнения объектов типа Paper по названию публикации
        public int Compare(Paper? x, Paper? y)
        {
            if ((x == null) || (y == null))
                throw new Exception("Невозможно сравнить элементы");
            return x.title.CompareTo(y.title);
        }
    }
}
