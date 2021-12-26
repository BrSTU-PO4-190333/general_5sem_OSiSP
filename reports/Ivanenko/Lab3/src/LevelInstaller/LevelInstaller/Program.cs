using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace LevelInstaller
{
    public class Installer
    {
        private const int Port = 8005; 
        private const string Address = "127.0.0.1";

        public void Update()
        {
            var levelData = "";
            try
            {
                var ipPoint = new IPEndPoint(IPAddress.Parse(Address), Port);
 
                var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                socket.Connect(ipPoint);
                const string message = "invoke message";
                var data = Encoding.Unicode.GetBytes(message!);
                socket.Send(data);
 
                data = new byte[256]; 
                var builder = new StringBuilder();

                do
                {
                    var bytes = socket.Receive(data, data.Length, 0);
                    builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                }
                while (socket.Available > 0);
                Console.WriteLine("response: " + builder);
                levelData = builder.ToString();
 
                socket.Shutdown(SocketShutdown.Both);
                socket.Close();
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            
            var level = new Level(levelData);
            var installer = new LevelInstaller(level);
            installer.InstallLevel();
        }
    }
}