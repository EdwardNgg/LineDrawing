#include <iostream>

#include "shape/CubicCurve.h"
#include "shape/LineSegment.h"


CubicCurve::CubicCurve(double a_, double b_, double c_, double d_, int xMax_,
                       int yMax_)
    : a(a_), b(b_), c(c_), d(d_), xMax(xMax_), yMax(yMax_) {
  midpointAlgorithm();
}


void CubicCurve::midpointAlgorithm() {
  // Determine the initial point to start drawing (0, y0).
  int x = 0;
  int y = static_cast<int>(getY(x));

  if (a == 0 && b == 0) { // If the curve is linear,
    // Determine the final point to end the drawing (xMax, y1).
    const int x1 = xMax;
    const int y1 = static_cast<int>(getY(x1));

    // Create and display a line segment connecting the initial and final
    // points.
    LineSegment curve = LineSegment(x, y, x1, y1);
    path = curve.getPath();
  }

  // The curve is quadratic or cubic.
  // Plot the initial point.
  // Determine the behavior and concavity of the initial point.
  appendToPath(x, y);
  double p = d - y;
  const CubicCurve::Behavior behavior = getBehavior(x);
  const CubicCurve::Concavity concavity = getConcavity(x);

  if (behavior == Decreasing && concavity != Down) {
    // If the curve at (0, y0) is decreasing and concave up, start plotting the
    // quickly decreasing curve using the midpoint algorithm.
    midpointFastDecrease(x, y);
  } else if (behavior == Increasing && concavity != Up) {
    // If the curve at (0, y0) is increasing and concave up, start plotting the
    // quickly increasing curve using the midpoint algorithm.
    midpointFastIncrease(x, y);
  } else if (behavior != Decreasing && concavity == Up) {
    // If the curve at (0, y0) is increasing and concave down, start plotting
    // the slowly increasing curve using the midpoint algorithm.
    midpointSlowIncrease(x, y);
  } else if (concavity == Down) {
    // If the curve at (0, y0) is decreasing and concave down, start plotting
    // the slowly decreasing curve using the midpoint algorithm.
    midpointSlowDecrease(x, y);
  } else if (6 * a < 0) {
    // If the curve is not concave at the point, but it will become concave
    // down, start plotting the slowly decreasing curve using the midpoint
    // algorithm.
    midpointSlowDecrease(x, y);
  } else {
    // If the curve is not concave at the point, but it will become concave up,
    // start plotting the slowly increasing curve using the midpoint algorithm.
    midpointSlowIncrease(x, y);
  }
}

void CubicCurve::midpointFastIncrease(int x, int y) {
  // Plot the points for a rapidly increasing curve (m > 1) using the midpoint
  // algorithm.
  double p = getDecisionParameter(x + 0.5, y + 1);

  // Plot while the curve is still rapidly increasing and in the window.
  while (getSlope(x) >= 1 && isInWindow(x, y)) {
    y ++;
    if (p < 0) {
      x ++;
      p += x * (3 * a * x + 4 * a + 2 * b) + 0.25 * a + c - 1;
    } else {
      p --;
    }
    appendToPath(x, y);
  }

  if (isInWindow(x, y)) {
    // If the curve has not traversed the window, continue the midpoint
    // algorithm for a slowly increasing curve.
    midpointSlowIncrease(x, y);
  }
}

void CubicCurve::midpointSlowIncrease(int x, int y) {
  // Plot the points for a slowly increasing curve (0 < m < 1) using the
  // midpoint algorithm.
  double p = getDecisionParameter(x + 1, y + 0.5);

  // Plot while the curve is still slowly increasing and in the window.
  while (getSlope(x) >= 0.0 && getSlope(x) <= 1.0 && isInWindow(x, y)) {
    // Common decision parameter increment
    const double pInc = x * (3 * a * x + 9 * a + 2 * b) - 7 * a + 2 * b + c;
    x ++;
    if (p < 0) {
      p += pInc;
    } else {
      y ++;
      p += pInc - 1;
    }
    appendToPath(x, y);
  }

  if (isInWindow(x, y)) {
    // If the curve is still in the window, decide how to plot the next curve.
    const CubicCurve::Concavity concavity = getConcavity(x);
    if (concavity == Up) {
      midpointFastIncrease(x, y);
    } else if (concavity == Down) {
      midpointSlowDecrease(x, y);
    } else {
      // There is no concavity at this point, indicating that the curve will
      // slowly increase.
      midpointSlowIncrease(x, y);
    }
  }
}

void CubicCurve::midpointSlowDecrease(int x, int y) {
  // Plot the points for a slowly decreasing curve (-1 < m < 1) using the
  // midpoint algorithm.
  double p = getDecisionParameter(x + 1, y - 0.5);

  // Plot while the curve is still slowly decreasing and in the window.
  while (getSlope(x) <= 0.0 && getSlope(x) >= - 1.0 && isInWindow(x, y)) {
    const double pInc = x * (3 * a * x + 9 * a + 2 * b) - 7 * a + 2 * b + c ;
    x ++;
    if (p < 0) {
      y --;
      p += pInc + 1;
    } else {
      p += pInc;
    }
    appendToPath(x, y);
  }

  if (isInWindow(x, y)) {
    // If the curve is still in the window, decide how to plot the next curve.
    const CubicCurve::Concavity concavity = getConcavity(x);
    if (concavity == Up) {
      midpointSlowIncrease(x, y);
    } else if (concavity == Down) {
      midpointFastDecrease(x, y);
    } else {
      // There is no concavity at this point, indicating that the curve will
      // slowly decrease.
      midpointSlowDecrease(x, y);
    }
  }
}

void CubicCurve::midpointFastDecrease(int x, int y) {
  // Plot the points for a rapidly decreasing curve (m < -1) using the midpoint
  // algorithm.
  double p = getDecisionParameter(x + 0.5, y - 1);

  // Plot while the curve is still rapidly decreasing and in the window.
  while (getSlope(x) <= -1.0 && isInWindow(x, y)) {
    y --;
    if (p < 0) {
      p ++;
    } else {
      x++;
      p += x * (3 * a * x + 2 * b) + 0.25 * a + c + 1;
    }
    appendToPath(x, y);
  }

  if (isInWindow(x, y)) {
    // If the curve has not traversed the window, continue the midpoint
    // algorithm for a slowly increasing curve.
    midpointSlowDecrease(x, y);
  }
}

double CubicCurve::getY(double x) const {
  return ((a * x + b) * x + c) * x + d;
}

double CubicCurve::getSlope(double x) const {
  return (3 * a * x + 2 * b) * x + c;
}

double CubicCurve::getAcceleration(double x) const {
  // Determines the acceleration or second derivative of the curve.
  return 6 * a * x + 2 * b;
}

double CubicCurve::getDecisionParameter(double x, double y) const {
  // Determines the decision parameter at the initial points for the curve
  // drawing midpoint algorithm.
  return a * x * x * x + b * x * x + c * x - y + d;
}

bool CubicCurve::isInWindow(int x, int y) const {
  // Determines if the point (x, y) is in the application window.
  return 0 <= x && x <= xMax && 0 <= y && y <= yMax;
}

CubicCurve::Behavior CubicCurve::getBehavior(double x) const {
  // Determines the behavior of the curve based on the first derivative or
  // slope at a point (x, y). The behavior of the curve is either increasing,
  // decreasing, or constant.
  const double m = getSlope(x);
  if (m < 0) {
    return Decreasing;
  }
  if (m > 0) {
    return Increasing;
  }
  return Constant;
}

CubicCurve::Concavity CubicCurve::getConcavity(double x) const {
  // Determines the concavity of the curve based on the second derivative or
  // acceleration at a point (x, y). The concavity of the curve is either up,
  // down, or none.
  const double dm = getAcceleration(x);
  if (dm < 0) {
    return Down;
  }
  if (dm > 0) {
    return Up;
  }
  return None;
}

