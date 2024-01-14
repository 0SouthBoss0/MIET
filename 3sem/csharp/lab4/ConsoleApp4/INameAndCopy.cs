namespace ConsoleApp4
{
    interface INameAndCopy
    {
        string Name { get; set; }
        object DeepCopy();
    }
}
