using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace MineSweeper
{
    /// <summary>
    /// 
    /// </summary>
    public class CellViewModel : INotifyPropertyChanged
    {
        public delegate void OnClick(CellViewModel cell);

        public bool bVisited { get; set; }

        public int Row { get; private set; }

        public int Column { get; private set; }

        private bool _isMine;
        public bool IsMine
        {
            get
            {
                return _isMine;
            }
            set
            {
                _isMine = value;
                OnPropertyChanged(new PropertyChangedEventArgs("IsMine"));
            }
        }

        private bool _isItRevealed;

        public bool IsItRevelaed {
            get
            {
                return _isItRevealed;
            }
            set
            {
                _isItRevealed = value;
                OnPropertyChanged(new PropertyChangedEventArgs("IsItRevelaed"));
                OnPropertyChanged(new PropertyChangedEventArgs("TextUI"));
                OnPropertyChanged(new PropertyChangedEventArgs("IsMine"));

            }
        }

        private int _numberOfNeighbours;

        public int NumberOfNighbourMines
        {
            get
            {
                return _numberOfNeighbours;
            }
            set
            {
                _numberOfNeighbours = value;
            }
        }

        public CellViewModel(int row,int column,bool isMine)
        {
            Row = row;
            Column = column;
            IsMine = isMine;
            NumberOfNighbourMines = -1;
        }

        

       

        /// <summary>
        /// 
        /// </summary>
        public string TextUI
        {

            get
            {
                if(IsItRevelaed)
                {
                    if (IsMine)
                    {
                        return "*";
                    }
                    else if (NumberOfNighbourMines > 0)
                    {
                        return NumberOfNighbourMines.ToString();
                    }
                    else
                    {
                        return "";
                    }
                }
                return "";
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            PropertyChanged?.Invoke(this, e);
        }

        private ICommand _onClickCommand;

        public ICommand OnClickCommand
        {
            get
            {
                if (_onClickCommand == null)
                {
                    _onClickCommand = new RelayCommand(
                        param => this.Click(),
                        param => this.CanClick()
                    );
                }
                return _onClickCommand;
            }
        }

        private bool CanClick()
        {
            // Verify command can be executed here
            //return !_isItRevealed;
            return true;
        }

        private void Click()
        {
            // Save command execution logic
            OnClickEvent?.Invoke(this);
        }

        public event OnClick OnClickEvent;
    }
}
