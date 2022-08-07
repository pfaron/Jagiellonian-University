namespace Parliament_Simulator
{
    public class TopicEventArgs : EventArgs
    {
        public string Topic { get; }

        public TopicEventArgs(string topic)
        {
            Topic = topic;
        }
    }
}