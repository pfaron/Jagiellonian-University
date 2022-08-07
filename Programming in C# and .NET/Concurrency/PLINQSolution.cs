using System.Net.NetworkInformation;

namespace Concurrency
{
    public class PLINQSolution
    {
        private readonly List<AddressEntry> _list;

        public PLINQSolution()
        {
            _list = FileUtil.ReadList();
        }
        public List<AddressStatus> Run()
        {
            var outputList = _list.AsParallel().WithDegreeOfParallelism(4)
                .Select(e => new AddressStatus(e, new Ping().Send(e.Address, 5000)))
                .OrderBy(e => e.Entry.Country).ToList();

            return outputList;
        }
    }
}