// ExerciseAlgo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<cmath>
#include<iostream>
#include<fstream>
#include<vector>


struct Point2D 
{
    double	x, y;
};
struct Circle
{
    Point2D centre;
    double radius;
};

/*
aM = DC − BE/AC − B^2
bM = AE − BD/AC − B^2
*/
/*
http://www.cs.bsu.edu/homepages/kjones/kjones/circles.pdf
*/
Circle SSM(const std::vector<Point2D> &vecPoints)
{
    Circle fitCircle;

    double sumOfXSquare =0, sumOfYSquare=0;
    double sumOfX = 0 , sumOfY =0;
    double sumOfProductOfXY =0;
    double sumOfXCube =0, sumOfYCube=0;
    double sumOfProductOfXandYSquare =0;
    double sumOfProductOfYandXSquare =0;

    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        sumOfX += vecPoints[i].x;
        sumOfY += vecPoints[i].y;

        sumOfXSquare += pow(vecPoints[i].x, 2);
        sumOfYSquare += pow(vecPoints[i].y, 2);

        sumOfXCube += pow(vecPoints[i].x, 3);
        sumOfYCube += pow(vecPoints[i].y, 3);

        sumOfProductOfXY += (vecPoints[i].x * vecPoints[i].y);

        sumOfProductOfXandYSquare += (vecPoints[i].x * pow(vecPoints[i].y, 2));
        sumOfProductOfYandXSquare += (vecPoints[i].y * pow(vecPoints[i].x, 2));
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
        std::cout << "In valid data points.";
        throw std::exception("Invalid data");
    }

    auto aM = ( ( D*C - B*E) / denominator);
    auto bM = ( (A*E - B*D) / denominator);

    double radius =0;

    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        radius += pow((vecPoints[i].x - aM), 2) + pow((vecPoints[i].y - bM), 2);
    }

    radius = sqrt(radius / n);

    fitCircle.centre.x = aM;
    fitCircle.centre.y = bM;
    fitCircle.radius = radius;

    return fitCircle;
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
    if (vecPoints.size() < 3)
    {
        std::cout << "In sufficient number of points";
        throw std::exception("In sufficient data");
    }
    auto circle = SSM(vecPoints);
    std::cout << "Circle center : (x,y) = (" << circle.centre.x << "," << circle.centre.y << ") with radius R = " << circle.radius;

    return 0;
}

