using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace WebServer
{
    public class Server
    {
        private const int Port = 8005;
        private const string LevelDataPath =
            @"/home/tuesdaydude/src/labworks-5-semester/MPP/Lab6/WebServer/WebServer/level.txt";

        public void Execute()
        {
            var ipPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), Port);
             
            var listenSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                listenSocket.Bind(ipPoint);
 
                listenSocket.Listen(10);
                
                while (true)
                {
                    var handler = listenSocket.Accept();
                    var builder = new StringBuilder();
                    var data = new byte[256]; 

                    do
                    {
                        var bytes = handler.Receive(data);
                        builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                    }
                    while (handler.Available>0);
 
                    Console.WriteLine(DateTime.Now.ToShortTimeString() + ": " + builder);
 
                    var levelData = File.ReadAllText(LevelDataPath);
                    data = Encoding.Unicode.GetBytes(levelData);
                    handler.Send(data);
                    File.Create(LevelDataPath).Close();

                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}