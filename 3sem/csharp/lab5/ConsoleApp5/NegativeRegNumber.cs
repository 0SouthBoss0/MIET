using System;

namespace ConsoleApp5
{
    internal class NegativeRegNumber: ApplicationException
    {
        public NegativeRegNumber(string message) : base(message) {}
    }
}
