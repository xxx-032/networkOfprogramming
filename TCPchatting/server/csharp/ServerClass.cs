using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace server
{
    public class ServerClass
    {
        private Socket serverSocket;
        private List<Socket> clientList;
        public ServerClass()
        {
            serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            clientList = new List<Socket>();
        }


        private void Accept()
        {
            Socket client = serverSocket.Accept();//每次接受一个客户端，循环调用获取N个用户，但会阻塞后面的代码，不会继续执行后面代码
            IPEndPoint clientDetail = client.RemoteEndPoint as IPEndPoint;
            Console.WriteLine("ip:" + clientDetail.Address + "通过port:" + clientDetail.Port + "连接服务器成功.");



            Thread clientReceive = new Thread(receive);
            clientReceive.IsBackground = true;
            clientReceive.Start(client);

            string msgStr = "ip:" + clientDetail.Address + "通过port:" + clientDetail.Port + "加入了聊天室.";
            BroadCast(null, msgStr);

            clientList.Add(client);

            Accept();
            //尾递归,因为background的关系.不会阻塞主线程一直监听用户
        }

        
        private void receive(object obj)
        {
            Socket serverPort = obj as Socket;
            IPEndPoint clientDetail = serverPort.RemoteEndPoint as IPEndPoint;
            try
            {
                byte[] msg = new byte[1024];
                int msgLen = serverPort.Receive(msg);

                BroadCast(serverPort, Encoding.UTF8.GetString(msg,0,msgLen));
                receive(serverPort);
            }catch
            {
                Console.WriteLine("ip:" + clientDetail.Address + "通过port:" + clientDetail.Port + "连接已经断开");
                clientList.Remove(serverPort);
            }
        }
        private void BroadCast(Socket toClient, string msg = "I'm fine")
        {
            foreach (var client in clientList)
            {
                if (client == toClient)
                {
                   
                }
                else
                {
                    client.Send(Encoding.UTF8.GetBytes(msg));
                }
            }
        }


        public void Start()
        {
            serverSocket.Bind(new IPEndPoint(IPAddress.Any, 33333));
            serverSocket.Listen(10);
            Console.WriteLine("服务器启动成功");
            Thread threadAccpet = new Thread(Accept);
            threadAccpet.IsBackground = true;
            threadAccpet.Start();

        }



    }
}
