using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POCApplication
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ChanelSignalA ch1_a = new ChanelSignalA("a", 1);
            ChanelSignalA ch1_b = new ChanelSignalA("b", 2);
            ChanelSignalA ch1_c = new ChanelSignalA("c", 3);

            ChanelSignalB ch2_a = new ChanelSignalB("a", 1);
            ChanelSignalB ch2_b = new ChanelSignalB("b", 2);
            ChanelSignalB ch2_c = new ChanelSignalB("c", 3);

            ChanelSignalC ch3_a = new ChanelSignalC("a", 1);
            ChanelSignalC ch3_b = new ChanelSignalC("b", 2);
            ChanelSignalC ch3_c = new ChanelSignalC("c", 3);

            MiniSphere s = new MiniSphere();

            Console.WriteLine("a=a");
            Console.WriteLine(s.AddChannel1(ch1_a));
            Console.WriteLine(s.AddChannel2(ch2_a));
            Console.WriteLine(s.AddChannel3(ch3_a));
            Console.WriteLine("b=b");
            Console.WriteLine(s.AddChannel1(ch1_b));
            Console.WriteLine(s.AddChannel2(ch2_b));
            Console.WriteLine(s.AddChannel3(ch3_b));
            PrintImagination(s.GetImagination());
            Console.WriteLine("c=c");
            Console.WriteLine(s.AddChannel1(ch1_c));
            Console.WriteLine(s.AddChannel2(ch2_c));
            Console.WriteLine(s.AddChannel3(ch3_c));
            PrintImagination(s.GetImagination());
            Console.WriteLine("a=b");
            Console.WriteLine(s.AddChannel1(ch1_a));
            Console.WriteLine(s.AddChannel2(ch2_a + ch2_b));
            Console.WriteLine(s.AddChannel3(ch3_b));
            PrintImagination(s.GetImagination());
            Console.WriteLine("b=c");
            Console.WriteLine(s.AddChannel1(ch1_b));
            Console.WriteLine(s.AddChannel2(ch2_b + ch2_c));
            Console.WriteLine(s.AddChannel3(ch3_c));
            PrintImagination(s.GetImagination());





        }

        public static void PrintImagination(List<Signal> signals)
        {
            Console.WriteLine($" IMAGINATION \t\t {signals[0]}\t\t{signals[2]}\t\t{signals[4]}");
            Console.WriteLine($" IMAGINATION \t\t {signals[1]}\t\t{signals[3]}\t\t{signals[5]}");
        }
    }
}
