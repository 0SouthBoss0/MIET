using System;

namespace ConsoleApp2
{
    class Paper
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
    }
}
