using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DllTestCs
{
    class FromDll
    {
        [DllImport(@"/Core.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern string encode_ascii(string inputText);

        [DllImport(@"/Core.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern string decode_ascii(string inputText);

        [DllImport(@"/Core.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern string get_last_error();

        public static string Encode(string userMessage)
        {
            string result = encode_ascii(userMessage);

            if (result == " ") throw new Exception(get_last_error());
            else return result;
        }

        public static string Decode(string userMessage)
        {
            string result = decode_ascii(userMessage);

            if (result == " ") throw new Exception(get_last_error());
            else return result;
        }
    }
}
