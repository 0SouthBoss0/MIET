
namespace ConsoleApp2
{
    interface INameAndCopy
    {
        string Name { get; set; }
        object DeepCopy();
    }
}
