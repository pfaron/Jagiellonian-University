using System.Text;

namespace LINQ_Exercises
{
    public static class Exercise3
    {
        public static void Run()
        {
            Console.WriteLine("Type names of cities in separate lines. \"X\" continues the program.");

            var cities = new List<string>();
            while (true)
            {
                var city = ConsoleUtil.ReadLineNotNull();

                if (city.Equals("X"))
                    break;

                cities.Add(city.ToUpper()[0] + city[1..]);
            }

            var citiesGrouped = cities.GroupBy(a => a[0]).ToDictionary(t => t.Key, t => t.OrderBy(p => p));

            while (true)
            {
                Console.WriteLine(
                    "Input letter. All cities starting with chosen letter will be displayed.\nTo finish type \"!\"");
                var line = ConsoleUtil.ReadLineNotNull().ToUpper();
                var letter = line[0];

                if (letter.Equals('!'))
                    break;

                if (!citiesGrouped.ContainsKey(letter))
                {
                    Console.WriteLine($"No cities starting with '{letter}'");
                    continue;
                }

                Console.WriteLine(string.Join(", ", citiesGrouped[letter]));

            }
        }
    }
}