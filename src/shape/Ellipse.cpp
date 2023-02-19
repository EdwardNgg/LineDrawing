#include "shape/Ellipse.h"


Ellipse::Ellipse(double x0_, double y0_, double x1_, double y1_) {
  int x0 = static_cast<int>(x0_);
  int y0 = static_cast<int>(y0_);
  int x1 = static_cast<int>(x1_);
  int y1 = static_cast<int>(y1_);

  int rx = std::abs(x1 - x0);
  int ry = std::abs(y1 - y0);

  midpointAlgorithm(x0, y0, rx, ry);
}

void Ellipse::midpointAlgorithm(int xc, int yc, int rx, int ry) {
  int rx2 = rx * rx;
  int ry2 = ry * ry;

  // *** Region 01 ***
  // Start drawing the ellipse at point (0, ry). Calculate the initial decision
  // parameter.
  int x = 0;
  int y = ry;
  double p = ry2 - rx2 * ry + 0.25 * rx2;
  ellipsePlotPoints(xc, yc, x, y);

  // While the tangent slope of the ellipse is less than -1.0, increment x and
  // decide which y to plot for each point. Plot clockwise.
  while (ry2 * x < rx2 * y) {
    x ++;
    if (p < 0) {
      p += 2 * ry2 * x + ry2;
    } else {
      y --;
      p += 2 * ry2 * x + ry2 - 2 * rx2 * y;
    }
    ellipsePlotPoints(xc, yc, x, y);
  }

  // *** Region 02 ***
  // Start drawing the second region of the ellipse starting at point (rx, 0).
  // Calculate the new decision parameter.
  x = rx;
  y = 0;
  p = rx2 - rx * ry2 + 0.25 * ry2;
  ellipsePlotPoints(xc, yc, x, y);

  // While the tangent slope of the ellipse is greater than -0.1, increment y
  // and which x to plot for each point. Plot counter-clockwise.
  while (ry2 * x >= rx2 * y) {
    y ++;
    if (p < 0) {
      p += rx2 + 2 * rx2 * y;
    } else {
      x --;
      p += 2 * rx2 * y + rx2 - 2 * ry2 * x;
    }
    ellipsePlotPoints(xc, yc, x, y);
  }
}


void Ellipse::ellipsePlotPoints(int xc, int yc, int x, int y) {
  appendToPath(xc + x, yc + y);
  appendToPath(xc - x, yc + y);
  appendToPath(xc - x, yc - y);
  appendToPath(xc + x, yc - y);
}
