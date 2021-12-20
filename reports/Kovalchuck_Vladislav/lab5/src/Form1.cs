using SimpleTcp;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TCPServer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        SimpleTcpServer server;
        private void btnStart_Click(object sender, EventArgs e)
        {
            server.Start();
            txtInfo.Text += $"Starting...{Environment.NewLine}";
            btnStart.Enabled = false;
            btnSend.Enabled = true;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            btnSend.Enabled = false;
            server = new SimpleTcpServer(txtIP.Text);
            server.Events.ClientConnected += Events_ClientConnected;
            server.Events.ClientDisconnected += Events_ClientDisconnected;
            server.Events.DataReceived += Events_DataReceived;
        }

        private void Events_DataReceived(object sender, DataReceivedEventArgs e)
        {
            this.Invoke((MethodInvoker)delegate
            {
                txtInfo.Text += $"{e.IpPort}: {Encoding.UTF8.GetString(e.Data)}{Environment.NewLine}";
            });            
        }

        private void Events_ClientDisconnected(object sender, ClientDisconnectedEventArgs e)
        {
            this.Invoke((MethodInvoker)delegate
            {
                txtInfo.Text += $"{e.IpPort} disconnected.{Environment.NewLine}";
                lstClientIP.Items.Remove(e.IpPort);
            });            
        }

        private void Events_ClientConnected(object sender, ClientConnectedEventArgs e)
        {
            this.Invoke((MethodInvoker)delegate
            {
                txtInfo.Text += $"{e.IpPort} connected.{Environment.NewLine}";
                lstClientIP.Items.Add(e.IpPort);
            });            
        }
        private void Send()
        {
            string IPAddress = "127.0.0.1";
            int Port = 9000;

            string Filename = @"D:\\UpdateFrom\\Update.zip";


            int bufferSize = 1024;
            byte[] buffer = null;
            byte[] header = null;


            FileStream fs = new FileStream(Filename, FileMode.Open);
            bool read = true;

            int bufferCount = Convert.ToInt32(Math.Ceiling((double)fs.Length / (double)bufferSize));



            TcpClient tcpClient = new TcpClient(IPAddress, Port);
            tcpClient.SendTimeout = 600000;
            tcpClient.ReceiveTimeout = 600000;

            string headerStr = "Content-length:" + fs.Length.ToString() + "\r\nFilename:" + @"D:\\UpdateFrom" + "Update.rar\r\n";
            header = new byte[bufferSize];
            Array.Copy(Encoding.ASCII.GetBytes(headerStr), header, Encoding.ASCII.GetBytes(headerStr).Length);

            tcpClient.Client.Send(header);

            for (int i = 0; i < bufferCount; i++)
            {
                buffer = new byte[bufferSize];
                int size = fs.Read(buffer, 0, bufferSize);

                tcpClient.Client.Send(buffer, size, SocketFlags.Partial);

            }

            tcpClient.Client.Close();

            fs.Close();
        }
        private void ShareFiles()
        {
            string oldPath = @"D:\UpdateFrom\Update";
            string newPath = @"D:\UpdateTo\Update";
            DirectoryInfo dirInfo = new DirectoryInfo(oldPath);
            if (dirInfo.Exists && Directory.Exists(newPath) == false)
            {
                dirInfo.MoveTo(newPath);
            }
        }
        private void btnSend_Click(object sender, EventArgs e)
        {
            if(server.IsListening)
            {
                if(!string.IsNullOrEmpty(txtMessage.Text)&&lstClientIP.SelectedItem!=null)
                {
                    string result = string.Empty;
                    if (cbChristmas.Checked)
                        result += 1;
                    else if(!cbChristmas.Checked)
                        result += 0;
                    if (cbNewLvl.Checked)
                        result += 1;
                    else if(!cbNewLvl.Checked)
                        result += 0;
                    result += txtVersion.Text;
                    result += txtMessage.Text;
                    server.Send(lstClientIP.SelectedItem.ToString(), result);
                    txtInfo.Text += $"Server: update sended.{Environment.NewLine}";
                    txtMessage.Text = string.Empty;
                    ShareFiles();
                }
            }
        }
    }
}
