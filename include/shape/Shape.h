#ifndef PA1_SHAPE_H
#define PA1_SHAPE_H

#include <vector>

#include <glm/glm.hpp>


class Shape
{
public:
    Shape() = default;

    virtual ~Shape() = 0;

    // return the points on this shape (in screen-space coordinate)
    const std::vector<glm::vec2> & getPath();

protected:
    /// add a point to the line
    /// \param x screen space coordinate
    /// \param y screen space coordinate
    void appendToPath(int x, int y);

    /// data buffer for all points this line segment passes through
    /// in screen-space
    std::vector<glm::vec2> path;
};


#endif  // PA1_SHAPE_H
