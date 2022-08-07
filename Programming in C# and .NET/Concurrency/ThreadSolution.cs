using System.Net.NetworkInformation;

namespace Concurrency
{
    public class ThreadSolution
    {
        private static readonly object Locker1 = new ();
        private static readonly object Locker2 = new ();

        private readonly Stack<AddressEntry> _stack;

        public ThreadSolution()
        {
            _stack = FileUtil.ReadStack();
        }
        
        private static void PingAll(Stack<AddressEntry> addresses, ICollection<AddressStatus> statuses)
        {
            while (true)
            {
                AddressEntry entry;
                lock (Locker1)
                {
                    if (addresses.TryPop(out var t))
                    {
                        entry = t;
                    }
                    else
                    {
                        break;
                    }
                }

                var ping = new Ping();
                var pingReply = ping.Send(entry.Address, 5000);

                lock (Locker2)
                {
                    statuses.Add(new AddressStatus(entry, pingReply));
                }
            }
        }

        public List<AddressStatus> Run()
        {
            var outputList = new List<AddressStatus>();

            const int numberOfThreads = 4;
            
            var threads = new Thread[numberOfThreads];
            for (var i = 0; i < numberOfThreads; i++)
            {
                threads[i] = new Thread(() => PingAll(_stack, outputList));
                threads[i].Start();
            }

            for (var i = 0; i < numberOfThreads; i++)
            {
                threads[i].Join();
            }

            outputList = outputList.OrderBy(e => e.Entry.Country).ToList();
            
            return outputList;

        }
    }
}