#ifndef PA1_LINESEGMENT_H
#define PA1_LINESEGMENT_H

#include <vector>

#include <glm/glm.hpp>

#include "shape/Shape.h"


class LineSegment : public Shape
{
public:
    LineSegment() = default;

    LineSegment(double x0_, double y0_, double x1_, double y1_);

    ~LineSegment() override = default;

protected:
    /// Bresenham line-drawing algorithm for line (x0, y0) -> (x1, y1)
    /// given that its slope |m| <= 1.0 and that (x0, y0) is start position
    /// \param x0        screen space coordinate
    /// \param y0        screen space coordinate
    /// \param x1        screen space coordinate
    /// \param y1        screen space coordinate
    /// \param transpose whether to transpose setPixel coordinates
    void bresenhamAlgorithm(int x0, int y0, int x1, int y1, bool transpose);
};



#endif  // PA1_LINESEGMENT_H
