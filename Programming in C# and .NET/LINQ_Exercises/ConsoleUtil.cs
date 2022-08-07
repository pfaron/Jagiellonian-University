namespace LINQ_Exercises;

public static class ConsoleUtil
{
    public static string ReadLineNotNull()
    {
        var temp = Console.ReadLine();
        while (temp == null)
        {
            Console.WriteLine("There has been an error getting user input. Please type again:");
            temp = Console.ReadLine();
        }

        return temp;
    }
}