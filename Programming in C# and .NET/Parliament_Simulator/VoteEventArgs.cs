namespace Parliament_Simulator
{
    public class VoteEventArgs : EventArgs
    {
        public bool Vote { get; }

        public VoteEventArgs(bool vote)
        {
            Vote = vote;
        }
    }
}