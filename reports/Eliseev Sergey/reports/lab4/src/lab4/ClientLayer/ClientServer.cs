using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace ClientLayer
{
    public class ClientServer
    {
        // адрес и порт сервера, к которому будем подключаться
        static int port = 8005; // порт сервера
        static string address = "127.0.0.1"; // адрес сервера

            public static void Main()
            {
            try
            {
                IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse(address), port);

                Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                // подключаемся к удаленному хосту
                socket.Connect(ipPoint);
                string path1 = @"C:\Users\Sergei\source\repos\lab1\lab1\MainWindow.xaml.cs";
                string path2 = @"C:\Users\Sergei\source\repos\lab4\lab1\MainWindow.xaml.cs";

                FileStream fs1;
                FileStream fs2;

                fs1 = new FileStream(path1, FileMode.Open, FileAccess.Read);
                fs2 = new FileStream(path2, FileMode.Open, FileAccess.Read);

                string message; 

                if (fs1.Length != fs2.Length)
                {
                    fs1.Close();
                    fs2.Close();
                    message = "Доступно обновление";
                }
                else
                {
                    message = "Обновления.нет";
                }
                byte[] data = Encoding.Unicode.GetBytes(message);
                socket.Send(data);

                // получаем ответ
                data = new byte[256]; // буфер для ответа
                StringBuilder builder = new StringBuilder();
                int bytes = 0; // количество полученных байт

                do
                {
                    bytes = socket.Receive(data, data.Length, 0);
                    builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                }
                while (socket.Available > 0);
                Console.WriteLine("ответ сервера: " + builder.ToString());

                // закрываем сокет
                socket.Shutdown(SocketShutdown.Both);
                socket.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.Read();
        }
    }
}
