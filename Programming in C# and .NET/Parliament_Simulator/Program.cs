namespace Parliament_Simulator
{
    internal static class Program
    {
        private static void Main()
        {
            Parliament parliament = new();
            UserInterface.GetUserInput(parliament);
        }
    }
}