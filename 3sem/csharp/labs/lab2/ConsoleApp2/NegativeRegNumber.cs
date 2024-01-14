using System;

namespace ConsoleApp2
{
    internal class NegativeRegNumber: ApplicationException
    {
        public NegativeRegNumber(string message) : base(message) {}
    }
}
