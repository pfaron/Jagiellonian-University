namespace Concurrency
{
    public static class FileUtil
    {
        public static Stack<AddressEntry> ReadStack()
        {
            var lines = File.ReadAllLines(PathToAddressesList());

            var stack = new Stack<AddressEntry>();
            for (var i = 1; i < lines.Length; i++)
            {
                var temp = lines[i].Split(';');
                stack.Push(new AddressEntry(temp[0], temp[1]));
            }

            return stack;
        }

        public static List<AddressEntry> ReadList()
        {
            var lines = File.ReadAllLines(PathToAddressesList());

            var list = new List<AddressEntry>();
            for (var i = 1; i < lines.Length; i++)
            {
                var temp = lines[i].Split(';');
                list.Add(new AddressEntry(temp[0], temp[1]));
            }

            return list;
        }

        private static string PathToAddressesList()
        {
            var directoryInfo = new DirectoryInfo(AppContext.BaseDirectory).Parent.Parent.Parent;
            return Path.GetFullPath(Path.Combine(directoryInfo.FullName, "addresses_list.txt"));
        }
    }
}