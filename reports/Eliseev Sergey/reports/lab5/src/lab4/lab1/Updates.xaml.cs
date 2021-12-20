using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using TRIPS_2;

namespace lab1
{
    /// <summary>
    /// Логика взаимодействия для Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        public Window1()
        {
            InitializeComponent();
        }

        public static void ReplaceFile(string path1, string path2)
        {
            File.Delete(path2);
            File.Copy(path1, path2);
        }
        private void Button_Yes(object sender, RoutedEventArgs e)
        {
            string path1 = @"C:\Users\Sergei\source\repos\lab1\lab1\MainWindow.xaml.cs";
            string path2 = @"C:\Users\Sergei\source\repos\lab4\lab1\MainWindow.xaml.cs";

                ReplaceFile(path1, path2);

                MainWindow newWindow = new MainWindow();
                Application.Current.MainWindow = newWindow;
                newWindow.Show();
                MessageBox.Show("Вы обновились!");
                Close();
        }

        private void Button_No(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Ну и оставайтесь на старой версии -_-");
            MainWindow newWindow = new MainWindow();
            Application.Current.MainWindow = newWindow;
            newWindow.Show();
            Close();
        }
    }
}
