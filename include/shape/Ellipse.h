#ifndef PA1_ELLIPSE_H
#define PA1_ELLIPSE_H

#include "shape/Shape.h"


class Ellipse : public Shape
{
public:
    Ellipse() = default;

    Ellipse(double x0_, double y0_, double x1_, double y1_);

    ~Ellipse() override = default;

protected:
    static inline int round(double a);

    /// Midpoint circle-drawing algorithm for ellipse centered at (xc, yc)
    /// and its radius of its 2 axes are rx, ry
    /// \param xc        screen space coordinate
    /// \param yc        screen space coordinate
    /// \param rx        screen space coordinate
    /// \param ry        screen space coordinate
    void midpointAlgorithm(int xc, int yc, int rx, int ry);

    /// Plot the point (x, y) in each ellipse quadrant
    /// \param xc x coordinate of center of circle
    /// \param yc y coordinate of center of circle
    /// \param x
    /// \param y
    void ellipsePlotPoints(int xc, int yc, int x, int y);
};


#endif  // PA1_ELLIPSE_H
