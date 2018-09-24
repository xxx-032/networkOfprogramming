using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace client
{
    public class ClientClass
    {
        private Socket clientSocket;

        public ClientClass()
        {
            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public void Send()
        {
            Thread threadSend = new Thread(readAndSend);
            //threadSend.IsBackground = true;
            threadSend.Start();
        }

        private void readAndSend()
        {
            string msg = "Hello!everyone!";
            while (msg != "quit")
            {
                clientSocket.Send(Encoding.UTF8.GetBytes(msg));
                msg = Console.ReadLine();
            }
        }

        private void receive()
        {
            try
            {
                byte[] msg = new byte[1024];
                int msgLen = clientSocket.Receive(msg);
                Console.WriteLine(Encoding.UTF8.GetString(msg, 0, msgLen));
                receive();
            }catch
            {
                Console.WriteLine("服务器已经断开连接.");
            }
           
        }

        public void Connect(string ip,int port)
        {
            clientSocket.Connect(IPAddress.Parse(ip), port);
            Console.WriteLine("连接服务器成功.");
            Thread clientReceive = new Thread(receive);
            clientReceive.IsBackground = true;
            clientReceive.Start();
        }
    }
}
