#pragma once

#include "Algorithm.h"

namespace LeastSquare
{

class MLSCovarianceAlgorithm : public Algorithm
{

public:
    Circle Fit(const std::vector<Point2D> &vecPoints) override;

};

}

