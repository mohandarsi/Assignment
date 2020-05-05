#pragma once

#include "Algorithm.h"

namespace LeastSquare
{

class MLSAlgorithm : public Algorithm
{
public:
    Circle Fit(const std::vector<Point2D> &vecPoints) override;
};

}

