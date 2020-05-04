
#include<fstream>
#include<iostream>

#include "Interfaces.h"
//#define DEBUG 1
extern void RunTests();

int main()
{
    std::ifstream input("inputs.txt");
    double x, y;
    std::vector<Point2D> vecPoints;
    while (input >> x >> y)
    {
        vecPoints.push_back({ x,y });
    }

    #ifdef DEBUG
        RunTests();
    #endif // DEBUG

    auto circle = SSM(vecPoints);
    std::cout << "Circle center : (x,y) = (" << circle.centre.x << "," << circle.centre.y << ") with radius R = " << circle.radius;

    return 0;
}