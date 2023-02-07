#include <algorithm>
#include <cmath>
#include <iostream>

#include "shape/LineSegment.h"


LineSegment::LineSegment(double x0_, double y0_, double x1_, double y1_)
{
    int x0 = static_cast<int>(x0_);
    int y0 = static_cast<int>(y0_);
    int x1 = static_cast<int>(x1_);
    int y1 = static_cast<int>(y1_);

    if (x0 == x1)
    {
        if (y0 == y1)  // P0 == P1, just one point
        {
            appendToPath(x0, y0);
        }
        else  // vertical line, slope m == infinity
        {
            // TODO:
            //  Derive all pixels passed by this line
            //  and call `appendToPath` for each of these pixels.
        }
    }
    else
    {
        if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        // at this point, we have x0 < x1, thus (x0, y0) is the start position and the slope m is finite
        double m = static_cast<double>(y1 - y0) / static_cast<double>(x1 - x0);

#ifdef DEBUG_LINE_SEGMENT
        std::cout << "m = " << m << '\n';
#endif

        if (m < -1.0)
        {
            // TODO:
            //  Call `bresenhamAlgorithm` with corresponding arguments.
            //  Hint: All these four cases (for slope) could be dealed with the function `bresenhamAlgorithm`.
            //        Just consider what arguments to pass in.
        }
        else if (m < 0)  // 1.0 < m < 0
        {
            // TODO:
            //  Call `bresenhamAlgorithm` with corresponding arguments.
            //  Hint: All these four cases (for slope) could be dealed with the function `bresenhamAlgorithm`.
            //        Just consider what arguments to pass in.
        }
        else if (m <= 1.0)  // 0 <= m <= 1.0
        {
            bresenhamAlgorithm(x0, y0, x1, y1, false);
        }
        else  // 1.0 < m
        {
            // TODO:
            //  Call `bresenhamAlgorithm` with corresponding arguments.
            //  Hint: All these four cases (for slope) could be dealed with the function `bresenhamAlgorithm`.
            //        Just consider what arguments to pass in.
        }
    }
}


void LineSegment::bresenhamAlgorithm(int x0, int y0, int x1, int y1, bool transpose)
{
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int yInc = (y1 > y0) ? 1 : -1;
    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);

    // NO need to determine which endpoint to use as start position
    // as (x0, y0) is guaranteed to be start position
    int x = x0;
    int y = y0;

    if (transpose)
    {
        appendToPath(y, x);
    }
    else
    {
        appendToPath(x, y);
    }

    while (x < x1)
    {
        x++;

        if (p < 0)
        {
            p += twoDy;
        }
        else
        {
            y += yInc;
            p += twoDyMinusDx;
        }

        if (transpose)
        {
            appendToPath(y, x);
        }
        else
        {
            appendToPath(x, y);
        }
    }
}
