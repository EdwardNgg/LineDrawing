#ifndef PA1_CUBICCURVE_H
#define PA1_CUBICCURVE_H

#include "shape/Shape.h"


class CubicCurve : public Shape
{
public:
    CubicCurve() = default;

    /// Cubic curve y = ax^3 + bx^2 + cx + d.
    /// `xMax_` and `yMax_` used to clip curve components outside of the screen (as optimization).
    /// B.t.w., so-called "xMin" == "yMin" == 0.
    CubicCurve(double a_, double b_, double c_, double d_, int xMax_, int yMax_);

    ~CubicCurve() override = default;

protected:
    void midpointAlgorithm();

    [[nodiscard]] double getY(double x) const;

    [[nodiscard]] double getSlope(double x) const;

private:
    double a {0};
    double b {0};
    double c {0};
    double d {0};
    int xMax {0};
    int yMax {0};
};


#endif  // PA1_CUBICCURVE_H
