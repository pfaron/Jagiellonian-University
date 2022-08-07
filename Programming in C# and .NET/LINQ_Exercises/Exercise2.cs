namespace LINQ_Exercises
{
    public static class Exercise2
    {
        public static void Run()
        {
            Console.WriteLine("Input number of rows and columns in separate lines.");
            if (!(int.TryParse(Console.ReadLine(), out var n) && int.TryParse(Console.ReadLine(), out var m)) ||
                n < 0 || m < 0)
            {
                Console.WriteLine("One of the numbers is incorrect.");
                return;
            }

            var rnd = new Random();
            rnd.Next();

            var numbers = Enumerable.Range(0, n)
                .Select(rowIndex => Enumerable.Range(0, m).Select(columnIndex => rnd.Next() % 10000).ToList()).ToList();

            numbers.ForEach(x =>
            {
                x.ForEach(y => Console.Write($"{y} "));
                Console.WriteLine();
            });
            Console.WriteLine($"Sum: {numbers.SelectMany(x => x).Sum()}");
            
        }
    }
}