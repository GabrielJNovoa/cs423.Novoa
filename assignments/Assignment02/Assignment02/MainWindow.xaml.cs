using System;
using System.Collections.Generic;
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

namespace Assignment02
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static int gridSize = 50;
        public static int stepSize = 800 / gridSize;

        public static int x = 800 / 2;
        public static int y = 800 / 2;
        public static int dir = 0;
        public static bool penDown = false;
        public static string command;

        public static System.Windows.Shapes.Rectangle rect;

        public MainWindow()
        {
            InitializeComponent();

            Console.Write("Enter Grid Size: ");
            gridSize = Convert.ToInt32(Console.ReadLine());
            stepSize = 800 / gridSize;

            x = 800/2;
            y = 800/2;
        }

        public void Execute(object sender, RoutedEventArgs e)
        {
            Console.WriteLine("enter command \n1: Pen Up \n2: Pen Down \n3: Turn Right \n4: Turn Left \n5: Move forward \n6: Clear Grid \n9 Terminate Program");
            command = Console.ReadLine();

            switch (command)
            {
                case "1":
                    penDown = false;
                    break;
                case "2":
                    penDown = true;
                    drawSquare(x, y, stepSize, true);
                    break;
                case "3":
                    dir = (dir - 1 + 4) % 4;
                    break;
                case "4":
                    dir = (dir + 1 + 4) % 4;
                    break;
                case "5":
                    switch (dir)
                    {
                        case 0:
                            x += stepSize;
                            break;
                        case 1:
                            y -= stepSize;
                            break;
                        case 2:
                            x -= stepSize;
                            break;
                        case 3:
                            y += stepSize;
                            break;
                    }
                    if (penDown)
                    {
                        drawSquare(x, y, stepSize, true);
                    }
                    break;
                case "6":
                    drawSquare(0, 0, 800, false);
                    break;
                case "9":
                    Environment.Exit(17);
                    break;
                default:
                    Console.WriteLine("Invalid Command");
                    break;
            }
        }

        public void drawSquare(int xpos, int ypos, int size, bool black)
        {
            rect = new System.Windows.Shapes.Rectangle();
            if (black)
            {
                rect.Stroke = new SolidColorBrush(Colors.Black);
                rect.Fill = new SolidColorBrush(Colors.Black);
            }
            else
            {
                rect.Stroke = new SolidColorBrush(Colors.White);
                rect.Fill = new SolidColorBrush(Colors.White);
            }

            rect.Width = size;
            rect.Height = size;

            Canvas.SetLeft(rect, xpos);
            Canvas.SetTop(rect, ypos);

            MainCanvas.Children.Add(rect);
        }
    }
}
