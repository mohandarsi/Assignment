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

namespace MineSweeper
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        BoardViewModel viewModel;
        
        
        public MainWindow()
        {
            InitializeComponent();
            this.WindowState = WindowState.Normal;
            this.WindowStyle = WindowStyle.SingleBorderWindow;
            this.ResizeMode = ResizeMode.NoResize;

            Rect workArea = System.Windows.SystemParameters.WorkArea;
            this.Left = (workArea.Width - this.Width) / 2 + workArea.Left;
            this.Top = (workArea.Height - this.Height) / 2 + workArea.Top;

            viewModel = new BoardViewModel(8, 8, 10);

            this.DataContext = viewModel;

            viewModel.GameOver += ViewModel_GameOver;
        }

        private void ViewModel_GameOver(GameStatusEventArgs args)
        {
            var message = string.Format("Game Over.. Moves {0} , Status :{1}", args.NumberOfMoves, args.IsWin ? "Winner" : "Looser");
            MessageBox.Show(message, "Status",MessageBoxButton.OK);
            Application.Current.Shutdown();
        }
    }
}
