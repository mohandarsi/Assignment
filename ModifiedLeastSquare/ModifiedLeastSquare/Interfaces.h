#pragma once

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

Circle SSM(const std::vector<Point2D> &vecPoints);