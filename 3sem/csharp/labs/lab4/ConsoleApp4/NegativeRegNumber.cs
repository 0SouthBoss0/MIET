using System;

namespace ConsoleApp4
{
    internal class NegativeRegNumber: ApplicationException
    {
        public NegativeRegNumber(string message) : base(message) {}
    }
}
