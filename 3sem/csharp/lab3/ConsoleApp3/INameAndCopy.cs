
namespace ConsoleApp3
{
    interface INameAndCopy
    {
        string Name { get; set; }
        object DeepCopy();
    }
}
