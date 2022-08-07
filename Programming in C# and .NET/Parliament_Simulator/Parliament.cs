namespace Parliament_Simulator
{
    public class Parliament
    {
        private readonly List<MemberOfParliament> _members = new();
        private readonly List<VotingData> _votings = new();
        private VotingData _currVotingData = VotingData.GetNoVotingData();
        
        private VotingStatusParliament _votingStatusParliament = VotingStatusParliament.NoVoting;

        private EventHandler<TopicEventArgs>? _votingStarted;
        private EventHandler? _votingEnded;


        public void StartVoting(string topic)
        {
            if (_votingStatusParliament != VotingStatusParliament.NoVoting)
            {
                Console.WriteLine("Can't start a new voting because there already is one.");
                return;
            }

            if (_members.Count == 0 || _votingStarted == null)
            {
                Console.WriteLine("Can't start a new voting because there are no members in parliament.");
                return;
            }
            
            _votingStatusParliament = VotingStatusParliament.VotingPresent;
            _currVotingData = new VotingData(topic);
            _votingStarted.Invoke(this, new TopicEventArgs(topic));

        }

        public void EndVoting()
        {
            if (_votingStatusParliament != VotingStatusParliament.VotingPresent)
            {
                Console.WriteLine("Can't end a voting because none is taking place.");
                return;
            }
            
            _votingStatusParliament = VotingStatusParliament.NoVoting;
            _votings.Add(_currVotingData);
            _currVotingData = VotingData.GetNoVotingData();
            _votingEnded?.Invoke(this, EventArgs.Empty);

        }

        public VotingData GetLastVotingData()
        {
            return _votings.Count != 0 ? _votings.Last() : VotingData.GetNoVotingData();
        }

        private void GetVote(object? sender, VoteEventArgs e)
        {
            _currVotingData.NumberOfVotes++;
            if (e.Vote)
                _currVotingData.NumberOfPositiveVotes++;
        }

        private void AddMember()
        {
            MemberOfParliament tempMember = new(GetVote, _votingStatusParliament);
            
            _votingStarted += tempMember.VotingStarted;
            _votingEnded += tempMember.VotingEnded;
            
            _members.Add(tempMember);
        }

        public void AddMembers(int numberOfMembers)
        {
            if (VotingIsTakingPlace())
            {
                Console.WriteLine("Can't add members when in middle of voting.");
                return;
            }

            while (numberOfMembers-- > 0)
            {
                AddMember();
            }
        }

        private void RemoveMember()
        {
            if (_members.Count == 0) return;
            var tempMember = _members.Last();
                
            _votingStarted -= tempMember.VotingStarted;
            _votingEnded -= tempMember.VotingEnded;
                
            _members.RemoveAt(_members.Count - 1);
        }

        public void RemoveMembers(int numberOfMembers)
        {
            if (VotingIsTakingPlace())
            {
                Console.WriteLine("Can't remove members when in middle of voting.");
                return;
            }
            
            while (numberOfMembers-- > 0)
            {
                RemoveMember();
            }
        }

        public MemberOfParliament GetMemberByNumber(int number)
        {
            return _members[number];
        }

        public int GetNumberOfMembers()
        {
            return _members.Count;
        }

        public VotingData GetCurrentVotingData()
        {
            return _currVotingData;
        }

        private bool VotingIsTakingPlace()
        {
            return _votingStatusParliament == VotingStatusParliament.VotingPresent;
        }
        
    }
}