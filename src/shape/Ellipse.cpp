#include "shape/Ellipse.h"


Ellipse::Ellipse(double x0_, double y0_, double x1_, double y1_)
{
    int x0 = static_cast<int>(x0_);
    int y0 = static_cast<int>(y0_);
    int x1 = static_cast<int>(x1_);
    int y1 = static_cast<int>(y1_);

    int rx = std::abs(x1 - x0);
    int ry = std::abs(y1 - y0);

    midpointAlgorithm(x0, y0, rx, ry);
}


inline int Ellipse::round(double a)
{
    // TODO:
    //  Implement a proper `round` function (consider round-off errors!)
    //  and you might get rid of those "ill-shaped" ellipsis
    //  (if you do encounter them)
}


void Ellipse::midpointAlgorithm(int xc, int yc, int rx, int ry)
{
    // TODO: Refer to attached materials
}


void Ellipse::ellipsePlotPoints(int xc, int yc, int x, int y)
{
    // TODO: Refer to attached material
}
