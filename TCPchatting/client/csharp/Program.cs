using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    class Program
    {
        static void Main(string[] args)
        {
            ClientClass client = new ClientClass();
            client.Connect("127.0.0.1", 33333);

            client.Send();
            
            Console.ReadLine();
        }
    }
}
