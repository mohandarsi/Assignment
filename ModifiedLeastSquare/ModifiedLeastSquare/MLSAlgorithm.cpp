// ExerciseAlgo.cpp : Defines the entry point for the console application.
//

#include<cmath>
#include<iostream>

#include "MLSAlgorithm.h"
#include "Interfaces.h"

namespace LeastSquare
{

/*
aM = DC − BE/AC − B^2
bM = AE − BD/AC − B^2
*/
/*
http://www.cs.bsu.edu/homepages/kjones/kjones/circles.pdf
*/

Circle MLSAlgorithm::Fit(const std::vector<Point2D> &vecPoints)
{
    if (vecPoints.size() < 3)
    {
        std::cout << "In sufficient number of points" << std::endl;
        throw std::exception("In sufficient data");
    }

    double sumOfXSquare = 0, sumOfYSquare = 0;
    double sumOfX = 0, sumOfY = 0;
    double sumOfProductOfXY = 0;
    double sumOfXCube = 0, sumOfYCube = 0;
    double sumOfProductOfXandYSquare = 0;
    double sumOfProductOfYandXSquare = 0;

    for each (const auto &point in vecPoints)
    {
        sumOfX += point.x;
        sumOfY += point.y;

        sumOfXSquare += pow(point.x, 2);
        sumOfYSquare += pow(point.y, 2);

        sumOfXCube += pow(point.x, 3);
        sumOfYCube += pow(point.y, 3);

        sumOfProductOfXY += (point.x * point.y);

        sumOfProductOfXandYSquare += (point.x * pow(point.y, 2));
        sumOfProductOfYandXSquare += (point.y * pow(point.x, 2));
    }

    auto n = vecPoints.size();

    double A = (n * sumOfXSquare) - pow(sumOfX, 2);
    double B = (n*sumOfProductOfXY) - (sumOfX * sumOfY);
    double C = (n * sumOfYSquare) - pow(sumOfY, 2);
    double d1 = (n* sumOfProductOfXandYSquare) - (sumOfX * sumOfYSquare);
    double d2 = (n* sumOfXCube) - (sumOfX * sumOfXSquare);
    double D = 0.5*(d1 + d2);

    double e1 = (n* sumOfProductOfYandXSquare) - (sumOfY * sumOfXSquare);
    double e2 = (n* sumOfYCube) - (sumOfY * sumOfYSquare);
    double E = 0.5*(e1 + e2);

    auto denominator = ((A*C) - (pow(B, 2)));
    if (denominator == 0)
    {
        std::cout << "In valid data points." << std::endl;
        throw std::exception("Invalid data");
    }

    auto aM = ((D*C - B*E) / denominator);
    auto bM = ((A*E - B*D) / denominator);

    double radius = 0;

    for each (const auto &point in vecPoints)
    {
        //radius += pow((vecPoints[i].x - aM), 2) + pow((vecPoints[i].y - bM), 2);
        radius += sqrt(pow((point.x - aM), 2) + pow((point.y - bM), 2));
    }

    //radius = sqrt(radius / n);
    radius = (radius / n);


    return { { aM,bM },radius };

}

}



