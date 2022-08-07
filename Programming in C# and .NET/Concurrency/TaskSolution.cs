using System.Net.NetworkInformation;

namespace Concurrency
{
    public class TaskSolution
    {
        private readonly List<AddressEntry> _list;

        public TaskSolution()
        {
            _list = FileUtil.ReadList();
        }
        public async Task<List<AddressStatus>> Run()
        {

            var outputListTasks = _list.Select(e => Task.Run(() =>
                {
                    var ping = new Ping();
                    var pingReply = ping.Send(e.Address, 5000);
                    return new AddressStatus(e, pingReply);
                }
            )).ToList();
            await Task.WhenAll(outputListTasks);

            var outputList = outputListTasks.Select(e => e.Result).ToList();

            return outputList;
        }
    }
}