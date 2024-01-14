namespace ConsoleApp5
{
    interface INameAndCopy
    {
        string Name { get; set; }
        object DeepCopy();
    }
}
