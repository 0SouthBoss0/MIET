using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp4
{
    // вспомогательный класс, реализующий интерфейс IComparer<Paper>,
    // который можно использовать для сравнения объектов типа Paper по фамилии автора публикации.

    class PaperSurname : IComparer<Paper>
    {
        public int Compare(Paper? x, Paper? y)
        {
            if ((x == null) || (y == null))
                throw new Exception("Невозможно сравнить элементы");
            return x.author.Surname.CompareTo(y.author.Surname);
        }
    }
}
