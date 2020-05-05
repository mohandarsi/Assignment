
#include<fstream>
#include<iostream>

#include "Circle2DFit.h"

#include "MLSAlgorithm.h"
#include "MLSCovarianceAlgorithm.h"

#include "Interfaces.h"

using namespace LeastSquare;
auto runtests = false;

namespace Tests
{
    void RunTests();
}

int main()
{
    std::ifstream input("inputs.txt");
    double x, y;
    std::vector<Point2D> vecPoints;
    while (input >> x >> y)
    {
        vecPoints.push_back({ x,y });
    }

    auto circleFit = std::make_unique<Circle2DFit>(std::make_unique<MLSAlgorithm>());

    auto circle = circleFit->Fit(vecPoints);

    std::cout << "Circle center : (x,y) = (" << circle.centre.x << "," << circle.centre.y << ") with radius R = " << circle.radius << std::endl;

    if (runtests)
    {
        Tests::RunTests();
    }

    return 0;
}