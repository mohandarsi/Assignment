using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MineSweeper
{
    public class GameStatusEventArgs : EventArgs
    {
        public int NumberOfMoves { get; }
        public bool IsWin { get; }
        public GameStatusEventArgs(int moves,bool win)
        {
            NumberOfMoves = moves;
            IsWin = win;
        }

    }
    public class BoardViewModel : INotifyPropertyChanged
    {
        int _numberOfRows;
        int _numberOfColumns;
        int _numberOfMines;
        int _numberOfMoves;
        CellViewModel[,] _cellViewModels;

        static int[] x = new int[8] { 0, -1, -1, -1, 0, 1, 1, 1 };
        static int[] y = new int[8] { -1, -1, 0, 1, 1, 1, 0, -1 };

        public delegate void OnGameOver(GameStatusEventArgs eventArgs);
        bool _isGameOver;
        public bool IsGameOver
        {
            get
            {
                return _isGameOver;
            }
            set
            {
                _isGameOver = true;
                OnPropertyChanged(new PropertyChangedEventArgs("IsGameOver"));
            }
        }

        /// <summary>
        /// Cell to bind into itemsource.
        /// </summary>

        IList<IList<CellViewModel>> _cells;
        public IList<IList<CellViewModel>> Cells
        {
            get
            {
                if (_cells == null)
                {
                    _cells = new List<IList<CellViewModel>>();
                    for (int i = 0; i < _cellViewModels.GetLength(0); i++)
                    {
                        _cells.Add(new List<CellViewModel>());
                        for (int j = 0; j < _cellViewModels.GetLength(1); j++)
                        {
                            _cells[i].Add(_cellViewModels[i, j]);
                        }
                    }
                }
                return _cells;
            }
        }


        bool isValidCell(int row, int column)
        {
            if (row >= 0 && row < _numberOfRows &&
               column >= 0 && column < _numberOfColumns)
            {
                return true;
            }

            return false;
        }

        bool isDone()
        {
            int totalEmptyCells = (_numberOfRows * _numberOfColumns) - _numberOfMines;
            int openedCells = 0;
            for (int i = 0; i < _numberOfRows; ++i)
            {
                for (int j = 0; j < _numberOfColumns; j++)
                {
                    if(_cellViewModels[i,j].IsItRevelaed && !_cellViewModels[i, j].IsMine)
                    {
                        openedCells++;
                    }
                }
            }
            if (openedCells == totalEmptyCells)
            {
                return true;
            }
            return false;
            
        }

        public BoardViewModel(int rows,int columns,int mines)
        {
            _numberOfRows = rows;
            _numberOfColumns = columns;
            _numberOfMines = mines;

            Initialize();
        }

        void Initialize()
        {
            _cellViewModels = new CellViewModel[_numberOfRows, _numberOfColumns];
            
            for (int i = 0; i < _numberOfRows; ++i)
            {
                for (int j = 0; j < _numberOfColumns; j++)
                {
                    _cellViewModels[i,j] = new CellViewModel(i,j,false);
                    _cellViewModels[i, j].OnClickEvent += OnCellClick;
                }
            }

            Random random = new Random();
            for (var mines = 0; mines< _numberOfMines;)
            {
                var x1 =random.Next(_numberOfRows);
                var y1 =random.Next(_numberOfColumns);
                if (!_cellViewModels[x1, y1].IsMine)
                {
                    _cellViewModels[x1, y1].IsMine = true;
                    Console.WriteLine("Mine activated at {0},{1}", x1, y1);
                    ++mines;
                }
            }
        }

        int GetNeighbourMines(int row, int column)
        {
            int mines = 0;
            for (int i = 0; i < x.Length; ++i)
            {
                if (isValidCell(row + x[i], column + y[i]))
                {
                    Console.WriteLine("visiting {0} ,{1}", row + x[i], column + y[i]);
                    if (_cellViewModels[row + x[i], column + y[i]].IsMine)
                    {
                        mines++;
                    }
                }
            }
            return mines;
        }

        void CalculateNeighbourMines(int row, int column)
        {
            if (_cellViewModels[row, column].IsItRevelaed)
            {
                return;
            }
            int mines;
            if (_cellViewModels[row, column].bVisited)
            {
                mines = _cellViewModels[row, column].NumberOfNighbourMines;
            }
            else
            {
                mines = GetNeighbourMines(row, column);
                _cellViewModels[row, column].bVisited = true;
            }
            if (mines > 0)
            {
                _cellViewModels[row, column].NumberOfNighbourMines = mines;
                _cellViewModels[row, column].IsItRevelaed = true;
            }
            else
            {
                _cellViewModels[row, column].NumberOfNighbourMines = 0;
                _cellViewModels[row, column].IsItRevelaed = true;
               
                for (int i = 0; i < x.Length; ++i)
                {
                    if (isValidCell(row + x[i], column + y[i]) && 
                        (!_cellViewModels[row + x[i], column + y[i]].IsMine))
                    {
                        CalculateNeighbourMines(row + x[i], column + y[i]);
                    }
                }
            }
        }

      
        public event PropertyChangedEventHandler PropertyChanged;
        public event OnGameOver GameOver;

        public void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            PropertyChanged?.Invoke(this, e);
        }

        public void OnCellClick(CellViewModel cell)
        {
            int row = cell.Row;
            int column = cell.Column;
            bool gameOver = false;
            if (!_cellViewModels[row, column].IsMine)
            {
                CalculateNeighbourMines(row, column);
                _numberOfMoves++;
            }
            else
            {
                //GameOver Display Board.
                gameOver = true;
               
            }
            if (isDone() || gameOver)
            {
                for (int i = 0; i < _numberOfRows; ++i)
                {
                    for (int j = 0; j < _numberOfColumns; j++)
                    {
                        if (_cellViewModels[i, j].IsMine)
                        {
                            _cellViewModels[i, j].IsItRevelaed = true;
                        }
                        _cellViewModels[i, j].OnClickEvent -= OnCellClick;
                    }
                }
                GameOver?.Invoke(new GameStatusEventArgs(_numberOfMoves, !gameOver));
                IsGameOver = true;
            }

        }

        
    }
}
