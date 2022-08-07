namespace Parliament_Simulator
{
    public static class BooleanGenerator
    {
        private static readonly Random Rnd;

        static BooleanGenerator()
        {
            Rnd = new Random();
        }

        public static bool NextBoolean()
        {
            return Rnd.Next(0, 2) == 1;
        }
    }
}