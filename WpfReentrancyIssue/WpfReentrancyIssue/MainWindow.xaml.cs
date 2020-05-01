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

namespace WpfReentrancyIssue
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ViewModel _viewModel;
        public MainWindow()
        {
            InitializeComponent();

            _viewModel = new ViewModel();
            // The DataContext serves as the starting point of Binding Paths
            DataContext = _viewModel;

            textBox.TextChanged += TextBoxTextChanged;
        }
        protected void TextBoxTextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            Console.WriteLine($"Begin event handler.TextBox.Text {box.Text} value: Reverting");
            _viewModel.Text = new string(box.Text.Reverse().ToArray());
            Console.WriteLine($"End event handler");
        }
    }
}
