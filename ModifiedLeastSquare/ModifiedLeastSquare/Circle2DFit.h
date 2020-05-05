#pragma once

#include<vector>
#include<memory>

namespace LeastSquare
{

class Algorithm;
struct Circle;
struct Point2D;
class Circle2DFit
{
public:
    Circle2DFit(std::unique_ptr<Algorithm> algorithm);
    Circle Fit(const std::vector<Point2D> &vecPoints);
private:
    std::unique_ptr<Algorithm> m_algorithm;
};

}
