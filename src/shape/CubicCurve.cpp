#include "shape/CubicCurve.h"


CubicCurve::CubicCurve(double a_, double b_, double c_, double d_, int xMax_, int yMax_)
        : a(a_), b(b_), c(c_), d(d_), xMax(xMax_), yMax(yMax_)
{
    midpointAlgorithm();
}


void CubicCurve::midpointAlgorithm()
{
    // TODO: Implement cubic curve
}


double CubicCurve::getY(double x) const
{
    return ((a * x + b) * x + c) * x + d;
}


double CubicCurve::getSlope(double x) const
{
    return (3 * a * x + 2 * b) * x + c;
}

