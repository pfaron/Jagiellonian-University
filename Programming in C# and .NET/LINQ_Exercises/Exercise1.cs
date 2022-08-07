namespace LINQ_Exercises
{
    public static class Exercise1
    {
        public static void Run()
        {
            Console.WriteLine("Input a positive integer.");
            if (!int.TryParse(Console.ReadLine(), out var num) || num < 0)
            {
                Console.WriteLine("Incorrect number.");
                return;
            }

            var numbers = Enumerable.Range(0, num + 1)
                .Where(x => (x != 5) && (x != 9) && (x % 2 != 0 || x % 7 == 0)).Select(x => x * x);

            var numbersArray = numbers as int[] ?? numbers.ToArray();

            Console.WriteLine("Sum of elements: {0}", numbersArray.Sum());
            Console.WriteLine("Number of elements: {0}", numbersArray.Length);
            Console.WriteLine("First element: {0}", numbersArray.First());
            Console.WriteLine("Last element: {0}", numbersArray.Last());
            if (numbersArray.Length >= 3)
                Console.WriteLine("Third element: {0}", numbersArray.Skip(2).First());

        }
    }
}