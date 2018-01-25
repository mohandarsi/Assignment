#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<queue>
using namespace std;
template<typename T> 
class Cell
{
public :
	Cell(T xcor,T ycor):m_x(xcor),m_y(ycor){}
	
	T GetX() const {
		return m_x;
	}
	T GetY() const
	{
		return m_y;
	}
	void Print() const
	{
		std::cout << "(X : " << m_x << " Y: " << m_y << ")";
	}

	T Slope(Cell<T> cell) const
	{
		T xdiff = cell.GetX() - m_x;
		T ydiff = cell.GetY() - m_y;
		return ydiff / xdiff;
	}

	bool operator ==(const Cell& rhs) const
	{
		return m_x == rhs.GetX() && m_y == rhs.GetY();
	}


	bool operator <(const Cell& rhs) const
	{
		if (m_x < rhs.GetX()) return true;
		if (m_x > rhs.GetX()) return false;
		if (m_y < rhs.GetY()) return true;
		return false;
	}

private:
	T m_x, m_y;

};
template<typename T>
int DiagnolCellCount(vector<Cell<T>>  vecPoints)
{
	int n = vecPoints.size();
	if (n < 2)
		return 0;

	std::set< Cell<T> > totalDiagnolCells;

	//  looping for each cell
	for (int i = 0; i < n; i++)
	{
		vector< Cell<T> > dignolCells;
		
		//push the current point
		dignolCells.push_back(vecPoints[i]);

		//  looping from next cell
		for (int j = i + 1; j < n; j++)
		{
			//ignore cells on same line horizontal/vertical
			if (vecPoints[i] == vecPoints[j] || vecPoints[i].GetX() == vecPoints[j].GetX() ||
				vecPoints[i].GetY() == vecPoints[j].GetY())
				continue;
			else
			{
				if (static_cast<int>(abs(vecPoints[i].Slope(vecPoints[j]))) == 1)
				{
					dignolCells.push_back(vecPoints[j]);
				}
			}
		}
		if (dignolCells.size() >= 2)
		{
			for each (auto cell in dignolCells)
			{
				cell.Print();
				auto result = totalDiagnolCells.insert(cell);
			}
			cout << endl;
		}
	}
	return totalDiagnolCells.size();

}


int main()
{

	int noTestcases;
	cin >> noTestcases;
	while (noTestcases > 0)
	{
		vector< Cell<int> > vecPoints;
		int points;
		cin >> points;
		for (int i = 0; i < points; i++)
		{
			int x1, y1;
			cin >> x1 >> y1;
			Cell<int> temp(x1, y1);
			vecPoints.push_back(temp);
		}
		cout << DiagnolCellCount(vecPoints) << endl;
		noTestcases--;
	}
}