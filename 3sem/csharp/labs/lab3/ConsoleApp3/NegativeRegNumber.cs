using System;

namespace ConsoleApp3
{
    internal class NegativeRegNumber: ApplicationException
    {
        public NegativeRegNumber(string message) : base(message) {}
    }
}
