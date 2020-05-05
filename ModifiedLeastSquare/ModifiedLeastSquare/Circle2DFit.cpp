#include "Circle2DFit.h"
#include "Algorithm.h"
#include "Interfaces.h"

namespace LeastSquare
{

Circle2DFit::Circle2DFit(std::unique_ptr<Algorithm> algorithm) :m_algorithm(std::move(algorithm))
{
}

Circle Circle2DFit::Fit(const std::vector<Point2D> &vecPoints) 
{
    return m_algorithm->Fit(vecPoints);
}


}