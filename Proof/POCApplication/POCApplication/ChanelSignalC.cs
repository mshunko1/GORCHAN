using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POCApplication
{
    public class ChanelSignalC : Signal, IComparable<ChanelSignalC>
    {
        public ChanelSignalC(string name, int value) : base(name, value)
        {
        }

        public static ChanelSignalC operator +(ChanelSignalC a, ChanelSignalC b)
        {
            ChanelSignalC ret = new ChanelSignalC("", 0);
            ret._name = a._name + b._name;

            var a1 = a._value;
            var a2 = b._value;

            //доброта
            char[] result = new char[4];
            for (int i = 0; i < a1.Length; i++)
            {
                if ((a2[i] == '1' || a1[i] == '1'))
                {
                    result[i] = '1';
                }
                else
                {
                    result[i] = '0';
                }
            }

            return new ChanelSignalC(a._name + b._name, Convert.ToInt32(new string(result), 2));
        }

        public static bool operator >(ChanelSignalC a, ChanelSignalC b)
        {
            var a1 = Convert.ToInt32(new string(a._value), 2);
            var a2 = Convert.ToInt32(new string(b._value), 2);
            return a1 > a2;
        }

        public static bool operator <(ChanelSignalC a, ChanelSignalC b)
        {
            var a1 = Convert.ToInt32(new string(a._value), 2);
            var a2 = Convert.ToInt32(new string(b._value), 2);
            return a1 < a2;
        }

        public static bool operator ==(ChanelSignalC a, ChanelSignalC b)
        {
            var a1 = Convert.ToInt32(new string(a._value), 2);
            var a2 = Convert.ToInt32(new string(b._value), 2);
            return a1 == a2;
        }

        public static bool operator !=(ChanelSignalC a, ChanelSignalC b)
        {
            var a1 = Convert.ToInt32(new string(a._value), 2);
            var a2 = Convert.ToInt32(new string(b._value), 2);
            return a1 != a2;
        }

        public int CompareTo(ChanelSignalC other)
        {
            if (this > other)
            {
                return 1;
            }
            else if (this == other)
            {
                if (this._name.Length > other._name.Length)
                {
                    return 1;
                }
                else if (this._name.Length == other._name.Length)
                {
                    return 0;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return -1;
            }
        }
    }
}
