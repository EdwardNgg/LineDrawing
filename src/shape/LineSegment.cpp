#include <algorithm>
#include <cmath>
#include <iostream>

#include "shape/LineSegment.h"


LineSegment::LineSegment(double x0_, double y0_, double x1_, double y1_) {
  int x0 = static_cast<int>(x0_);
  int y0 = static_cast<int>(y0_);
  int x1 = static_cast<int>(x1_);
  int y1 = static_cast<int>(y1_);

  if (x0 == x1) {
    if (y0 == y1) {  // P0 == P1, just one point
      appendToPath(x0, y0);
    } else if (y0 < y1) { // vertical line, slope m == infinity
      for (int y = y0; y <= y1; y++) {
        appendToPath(x0, y);
      }
    } else { // vertical line, slope m == -infinity
      for (int y = y0; y >= y1; y--) {
        appendToPath(x0, y);
      }
    }
  } else {
    if (x0 > x1) {
      std::swap(x0, x1);
      std::swap(y0, y1);
    }

    // at this point, we have x0 < x1, thus (x0, y0) is the start position and the slope m is finite
    double m = static_cast<double>(y1 - y0) / static_cast<double>(x1 - x0);

#ifdef DEBUG_LINE_SEGMENT
    std::cout << "m = " << m << '\n';
#endif

    if (m < -1.0) {
      bresenhamAlgorithm(y1, x1, y0, x0, true);
    } else if (m < 0) { // 1.0 < m < 0
      bresenhamAlgorithm(x0, y0, x1, y1, false);
    } else if (m <= 1.0) {  // 0 <= m <= 1.0
      bresenhamAlgorithm(x0, y0, x1, y1, false);
    } else { // 1.0 < m
      bresenhamAlgorithm(y0, x0, y1, x1, true);
    }
  }
}


void LineSegment::bresenhamAlgorithm(int x0, int y0, int x1, int y1,
                                     bool transpose) {
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

  if (transpose) {
    appendToPath(y, x);
  } else {
    appendToPath(x, y);
  }

  while (x < x1) {
    x++;

    if (p < 0) {
      p += twoDy;
    } else {
      y += yInc;
      p += twoDyMinusDx;
    }

    if (transpose) {
      appendToPath(y, x);
    } else {
      appendToPath(x, y);
    }
  }
}
