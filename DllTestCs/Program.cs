using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DllTestCs
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                string choise;
                Console.Write("Encode or decode (only ASCII) (x to exit)? (e/d/x) > ");
                choise = Console.ReadLine();

                if ((choise[0] == 'e') || (choise[0] == 'd'))
                {
                    try
                    {
                        string userText;

                        Console.Write("Put your text here > ");
                        userText = Console.ReadLine();
                        Console.WriteLine($"Your text length: {userText.Length}");
                        string ed;
                    
                        if (choise[0] == 'e')
                        {
                            ed = FromDll.Encode(userText);
                            Console.WriteLine($"Your encoded text: {ed}\nLength: {ed.Length}");
                        }
                        if (choise[0] == 'd')
                        {
                            ed = FromDll.Decode(userText);
                            Console.WriteLine($"Your decoded text: {ed}\nLength: {ed.Length}");
                        }
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e.Message);
                    }
                }
                else if (choise[0] == 'x')
                {
                    break;
                }
                else Console.WriteLine("Wrong choice!");

                Console.WriteLine(String.Empty);
            }
        }
    }
}
