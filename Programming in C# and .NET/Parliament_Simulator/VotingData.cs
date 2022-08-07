namespace Parliament_Simulator
{
    public class VotingData
    {
        private static readonly VotingData NoVotingCurrently = new("No voting.");

        public static VotingData GetNoVotingData()
        {
            return NoVotingCurrently;
        }
        public string VotingTopic { get; }
        public int NumberOfVotes { get; set; }
        public int NumberOfPositiveVotes { get; set; }

        public VotingData(string topic)
        {
            VotingTopic = topic;
        }
    }
}