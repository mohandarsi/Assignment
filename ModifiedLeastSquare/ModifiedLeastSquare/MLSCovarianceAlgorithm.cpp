
#include<iostream>
#include<algorithm>

#include "MLSCovarianceAlgorithm.h"
#include "Interfaces.h"

namespace LeastSquare
{
/* Co variance implmentation based on article - C++ OpenCV -- Knowing Variance And Covariance
https://cppsecrets.com/users/2194110105107104105108981049711648504964103109971051084699111109/C00-OpenCV-Knowing-Variance-And-Covariance.php

*/

template<class T>
double mean(std::vector<T> arr)
{
    double sum = 0;
    for (int i = 0; i < arr.size(); i++)
        sum = sum + arr[i];
    return sum / arr.size();
}

template<class T>
double covariance(std::vector<T> arr1, std::vector<T> arr2)
{
    double sum = 0;
    auto meanOfArr1 = mean(arr1);
    auto meanOfArr2 = mean(arr2);
    for (int i = 0; i < arr1.size(); i++)
        sum = sum + (arr1[i] - meanOfArr1) * (arr2[i] - meanOfArr2);

    return sum / (arr1.size() - 1);
}

/*
http://www.cs.bsu.edu/homepages/kjones/kjones/circles.pdf
*/
Circle MLSCovarianceAlgorithm::Fit(const std::vector<Point2D> &vecPoints)
{
    if (vecPoints.size() < 3)
    {
        std::cout << "In sufficient number of points";
        throw std::exception("In sufficient data");
    }

    std::vector<double> vecXPoints;
    std::vector<double> vecYPoints;

    for each (const auto &point in vecPoints)
    {
        vecXPoints.push_back(point.x);
        vecYPoints.push_back(point.y);
    }

    auto n = vecPoints.size();

    /* A = n(n−1)Sx ^ 2 */

    auto Sx = covariance(vecXPoints, vecXPoints);
    auto A = n*(n - 1)*Sx;

    /* B = n(n−1)Sxy */

    auto Sxy = covariance(vecXPoints, vecYPoints);
    auto B = n*(n - 1)*Sxy;

    /* C = n(n−1)Sy ^2 */

    auto Sy = covariance(vecYPoints, vecYPoints);
    auto C = n*(n - 1)*Sy;

    /* D = 0.5n(n−1)(Sxy2 + Sxx2) */
    
    std::vector<double> vecY2Points{ vecYPoints };
    std::transform(vecY2Points.begin(), vecY2Points.end(), vecY2Points.begin(), vecY2Points.begin(), std::multiplies<double>());

    auto Sxy2 = covariance(vecXPoints, vecY2Points);

    std::vector<double> vecX2Points { vecXPoints };
    std::transform(vecX2Points.begin(), vecX2Points.end(), vecX2Points.begin(),vecX2Points.begin(), std::multiplies<double>());
   
    auto Sxx2 = covariance(vecXPoints, vecX2Points);

    auto D = 0.5*n*(n - 1)*(Sxy2 + Sxx2);

    /* E =0.5n(n−1)(Syx2 + Syy2) */
    auto Syx2 = covariance(vecYPoints, vecX2Points);
    auto Syy2 = covariance(vecYPoints, vecY2Points);
    auto E = 0.5*n*(n - 1)*(Syx2 + Syy2);

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


    return{ { aM,bM },radius };

}



}
