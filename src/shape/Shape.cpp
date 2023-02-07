#include <algorithm>

#include "shape/Shape.h"


Shape::~Shape() = default;


const std::vector<glm::vec2> &Shape::getPath() {
  return path;
}


void Shape::appendToPath(int x, int y) {
  path.emplace_back(x, y);
}


//void fun()
//{
//    double xNDC, c, yNDC, y, screenWidth, screenHeight, x, y;
//
//    // Screen space coordinate to NDC
//    // x: [0, screenWidth - 1] -> [-1, 1]
//    // y: [0, screenHeight - 1] -> [-1, 1]
//    xNDC = 2.0 * x / screenWidth - 1.0,
//    yNDC = 2.0 * y / screenHeight - 1.0;
//}
