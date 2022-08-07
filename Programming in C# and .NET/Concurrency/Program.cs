using System.Diagnostics;

namespace Concurrency
{
    internal static class Program
    {
        private static void Main()
        {
            
            var stopwatch = new Stopwatch();
            List<AddressStatus> outputList;

            var times = new long[3];

            
            var threadSolution = new ThreadSolution();
            
            stopwatch.Start();
            outputList = threadSolution.Run();
            stopwatch.Stop();

            times[0] = stopwatch.ElapsedMilliseconds;
            Display(outputList);
            stopwatch.Reset();
            
            
            var plinqSolution = new PLINQSolution();
            
            stopwatch.Start();
            outputList = plinqSolution.Run();
            stopwatch.Stop();
            
            times[1] = stopwatch.ElapsedMilliseconds;
            Display(outputList);
            stopwatch.Reset();

            
            var taskSolution = new TaskSolution();
            
            stopwatch.Start();
            outputList = taskSolution.Run().Result;
            stopwatch.Stop();
            
            times[2] = stopwatch.ElapsedMilliseconds;
            Display(outputList);
            stopwatch.Reset();
            
            
            Console.WriteLine("Thread solution time: " + times[0]);
            Console.WriteLine("PLINQ solution time: " + times[1]);
            Console.WriteLine("Task solution time: " + times[2]);
            
            Console.ReadKey();
        }
        
        private static void Display(List<AddressStatus> outputList)
        {
            foreach (var ((country, address), pingReply) in outputList)
            {
                Console.WriteLine(country + " " + address + " " + pingReply.Status);
            }
        }
    }
}