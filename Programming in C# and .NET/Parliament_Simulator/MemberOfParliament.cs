namespace Parliament_Simulator
{
    public class MemberOfParliament
    {
        private string _currVotingTopic = "";
        private VotingStatusMember _memberVotingStatus = VotingStatusMember.NotYetVoted;
        private VotingStatusParliament _parliamentVotingStatus;

        private readonly EventHandler<VoteEventArgs> _voted;

        public MemberOfParliament(EventHandler<VoteEventArgs> voted, VotingStatusParliament parliamentVotingStatus)
        {
            _voted += voted;
            _parliamentVotingStatus = parliamentVotingStatus;
        }

        public void Vote()
        {
            if (_parliamentVotingStatus == VotingStatusParliament.NoVoting)
            {
                Console.WriteLine("Can't vote now, no voting currently.");
                return;
            }

            if (_memberVotingStatus == VotingStatusMember.AlreadyVoted)
            {
                Console.WriteLine("Can't vote now, already voted.");
                return;
            }
            
            _voted.Invoke(this, new VoteEventArgs(BooleanGenerator.NextBoolean()));
            _memberVotingStatus = VotingStatusMember.AlreadyVoted;
        }

        public void VotingStarted(object? sender, TopicEventArgs e)
        {
            _currVotingTopic = e.Topic;
            _parliamentVotingStatus = VotingStatusParliament.VotingPresent;
        }

        public void VotingEnded(object? sender, EventArgs e)
        {
            _currVotingTopic = "";
            _parliamentVotingStatus = VotingStatusParliament.NoVoting;
        }
        
    }
}