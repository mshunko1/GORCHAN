using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POCApplication
{
    public class Signal
    {
        protected string _name;
        protected char[] _value = new char[4];
        public Signal(string name, int value) 
        {
            _name = name;
            var binary = Convert.ToString(value, 2).PadLeft(4, '0');
            for(int i = 0; i < binary.Length; i++)
            {
                _value[i] = binary[i];
            }
        }
        public bool IsNeutral()
        {
            return Convert.ToInt32(Convert.ToString(new string(_value)), 2) == 0 ? true : false;
        }
        public override string ToString()
        {
            return _name+":"+Convert.ToInt32(Convert.ToString(new string(_value)), 2).ToString();
        }
    }
}
