#include "shape/Circle.h"


Circle::Circle(double x0_, double y0_, double x1_, double y1_) {
  int x0 = static_cast<int>(x0_);
  int y0 = static_cast<int>(y0_);
  int x1 = static_cast<int>(x1_);
  int y1 = static_cast<int>(y1_);

  midpointAlgorithm(x0, y0, x1, y1);
}


void Circle::midpointAlgorithm(int x0, int y0, int x1, int y1) {
  // TODO: Refer to attached materials
}


void Circle::circlePlotPoints(int xc, int yc, const glm::ivec2 &pt) {
  // TODO: Refer to attached materials
}
