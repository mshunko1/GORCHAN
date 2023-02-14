using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POCApplication
{
    public class MiniSphere
    {
        List<ChanelSignalA> _signalsA=new List<ChanelSignalA>();
        List<ChanelSignalB> _signalsB=new List<ChanelSignalB>();
        List<ChanelSignalC> _signalsC=new List<ChanelSignalC>();

        Signal[] _imagination = new Signal[6];

        ChanelSignalA last_ch1;
        ChanelSignalB last_ch2;
        ChanelSignalC last_ch3;

        ChanelSignalA curr_ch1;
        ChanelSignalB curr_ch2;
        ChanelSignalC curr_ch3;
        public ChanelSignalA AddChannel1(ChanelSignalA signal)
        {
            last_ch1 = curr_ch1;
            if(_signalsA.Count == 0)
            {
                _signalsA.Add(signal);
                curr_ch1 = signal;
                return signal;
            }
            else
            {
                _signalsA = _signalsA.Select(i => i + signal).ToList();
                _signalsA.Add(signal);
            }
            var min =  _signalsA.Min();
            var max = _signalsA.Max();
            if (min.IsNeutral())
            {
                _signalsA.Remove(min);
                _signalsA.Remove(max);
            }
            curr_ch1 = min;
            return min;
        }
        public ChanelSignalB AddChannel2(ChanelSignalB signal)
        {
            last_ch2 = curr_ch2;
            if (_signalsB.Count == 0)
            {
                curr_ch2 = signal;
                _signalsB.Add(signal);
                return signal;
            }
            else
            {
                _signalsB = _signalsB.Select(i => i + signal).ToList();
                _signalsB.Add(signal);
            }
            var min = _signalsB.Min();
            var max = _signalsB.Max();
            if (min.IsNeutral())
            {
                _signalsB.Remove(min);
                _signalsB.Remove(max);
            }
            curr_ch2 = min;
            return min;
        }
        public ChanelSignalC AddChannel3(ChanelSignalC signal)
        {
            last_ch3 = curr_ch3;
            if (_signalsC.Count == 0)
            {
                curr_ch3 = signal;
                _signalsC.Add(signal);
                return signal;
            }
            else
            {
                _signalsC = _signalsC.Select(i => i + signal).ToList();
                _signalsC.Add(signal);
            }
            var min = _signalsC.Min();
            var max = _signalsC.Max();
            if (min.IsNeutral())
            {
                _signalsC.Remove(min);
                _signalsC.Remove(max);
            }
            curr_ch3 = min;
            return min;
        }
         
        public List<Signal> GetImagination()
        {
            if (curr_ch1 != null && last_ch1 != null)
            {
                _imagination[0] = last_ch1;
                _imagination[1] = curr_ch1;
            }
            else
            {
                throw new InvalidOperationException();
            }
            if (curr_ch2 != null && last_ch2 != null)
            {
                _imagination[2] = last_ch2;
                _imagination[3] = curr_ch2;
            }
            else
            {
                throw new InvalidOperationException();
            }
            if (curr_ch1 != null && last_ch3 != null)
            {
                _imagination[4] = last_ch3;
                _imagination[5] = curr_ch3;
            }
            else
            {
                throw new InvalidOperationException();
            }
            return _imagination.ToList();
        }
    }
}
