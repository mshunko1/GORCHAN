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
        public ChanelSignalA AddChannel1(ChanelSignalA signal)
        {
            if(_signalsA.Count == 0)
            {
                _signalsA.Add(signal);
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
            return min;
        }
        public ChanelSignalB AddChannel2(ChanelSignalB signal)
        {
            if (_signalsB.Count == 0)
            {
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
            return min;
        }
        public ChanelSignalC AddChannel3(ChanelSignalC signal)
        {
            if (_signalsC.Count == 0)
            {
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
            return min;
        }
    }
}
