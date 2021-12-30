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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Globalization;
using Microsoft.Win32;
using lab1;

namespace TRIPS_2
{
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        private void DrawingModeSelection(object sender, RoutedEventArgs e)
        {
            Ink.EditingMode = InkCanvasEditingMode.Ink;
        }

        private void DeletingModeSelection(object sender, RoutedEventArgs e)
        {
            Ink.EditingMode = InkCanvasEditingMode.EraseByStroke;
        }

        private void FormatingModeSelection(object sender, RoutedEventArgs e)
        {
            Ink.EditingMode = InkCanvasEditingMode.EraseByPoint;
        }

        private void ColorsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem selectedItem = (ComboBoxItem)(ColorsList.SelectedValue);
            string value = (string)(selectedItem.Content);
            Ink.DefaultDrawingAttributes.Color = (Color)ColorConverter.ConvertFromString(value);
        }

        private void BrushWidthChange(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            Ink.DefaultDrawingAttributes.Width = ChooseWidth.Value;
            Ink.DefaultDrawingAttributes.Height = ChooseWidth.Value;
        }

        private void CloseWindow_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void SaveControlImage(
    Visual baseElement, int imageWidth, int imageHeight, string pathToOutputFile)
        {
            // 1) get current dpi
            var pSource = PresentationSource.FromVisual(Application.Current.MainWindow);
            Matrix m = pSource.CompositionTarget.TransformToDevice;
            double dpiX = m.M11 * 96;
            double dpiY = m.M22 * 96;

            // 2) create RenderTargetBitmap
            var elementBitmap = new RenderTargetBitmap(imageWidth, imageHeight, dpiX, dpiY, PixelFormats.Default);

            // 3) undo element transformation
            var drawingVisual = new DrawingVisual();
            using (DrawingContext drawingContext = drawingVisual.RenderOpen())
            {
                var visualBrush = new VisualBrush(baseElement);
                drawingContext.DrawRectangle(
                    visualBrush,
                    null,
                    new Rect(new Point(0, 0), new Size(imageWidth / m.M11, imageHeight / m.M22)));
            }

            // 4) draw element
            elementBitmap.Render(drawingVisual);

            // 5) create PNG image
            var encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(elementBitmap));

            // 6) save image to file
            using (var imageFile = new FileStream(pathToOutputFile, FileMode.Create, FileAccess.Write))
            {
                encoder.Save(imageFile);
                imageFile.Flush();
                imageFile.Close();
            }
        }

        private string GetOutputFileName()
        {
            var dlgSave = new SaveFileDialog
            {
                DefaultExt = "png",
                Title = "Choose output file",
                Filter = "PNG Files|*.png"
            };

            if (dlgSave.ShowDialog() == true)
                return dlgSave.FileName;

            return string.Empty;
        }

        private void Btn_Save_Click(object sender, RoutedEventArgs e)
        {
            // get output file name
            string fileName = this.GetOutputFileName();
            if (fileName == string.Empty)
                return;

            // select visual element
            Visual element = null;
            var elementWidth = 0;
            var elementHeight = 0;

            element = this.Ink;
            elementWidth = (int)this.Ink.ActualWidth;
            elementHeight = (int)this.Ink.ActualHeight;


            // save selected element to file
            this.SaveControlImage(element, elementWidth, elementHeight, fileName);
        }

        private void Btn_About_Click(object sender, RoutedEventArgs e)
        {
            string A = "Елисеев Сергей, 3-й курс, ПО-4(1)\r\n" +
                "Моё приложение позволит вам реализовать свои фантазии на холсте";
            aboutdll.Class1.Show_About(A);

        }
    }
}
