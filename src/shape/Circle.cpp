#include "shape/Circle.h"

Circle::Circle(double x0_, double y0_, double x1_, double y1_) {
  int x0 = static_cast<int>(x0_);
  int y0 = static_cast<int>(y0_);
  int x1 = static_cast<int>(x1_);
  int y1 = static_cast<int>(y1_);

  midpointAlgorithm(x0, y0, x1, y1);
}


void Circle::midpointAlgorithm(int x0, int y0, int x1, int y1) {
  // Calculate the radius.
  int dx = std::abs(x1 - x0);
  int dy = std::abs(y1 - y0);
  int dx2 = dx * dx;
  int dy2 = dy * dy;
  int r = static_cast<int>(std::sqrt(dx2 + dy2));

  // Determine first point on the circle as (0, r) and decision parameter for
  // second point as p = 1 -r.
  // Note that the circle is translated such that the center is at (0, 0).
  int x = 0;
  int y = r;
  int p = 1 - r;
  circlePlotPoints(x0, y0, glm::ivec2(x, y));


  // Plot points based on symmetry, incrementing the decision parameter until
  // all points are determined in the second octant.
  while (x <= y) {
    x ++;
    if (p < 0) {
      p += 2 * x + 1;
    } else {
      y --;
      p += 2 * x + 1 - 2 * y;
    }
    circlePlotPoints(x0, y0, glm::ivec2(x, y));
  }

}


void Circle::circlePlotPoints(int xc, int yc, const glm::ivec2 &pt) {
  appendToPath(xc + pt.x, yc + pt.y);
  appendToPath(xc - pt.x, yc + pt.y);
  appendToPath(xc - pt.y, yc + pt.x);
  appendToPath(xc - pt.y, yc - pt.x);
  appendToPath(xc - pt.x, yc - pt.y);
  appendToPath(xc + pt.x, yc - pt.y);
  appendToPath(xc + pt.y, yc - pt.x);
  appendToPath(xc + pt.y, yc + pt.x);
}
