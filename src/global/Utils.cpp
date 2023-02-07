#include <iostream>

#include <glm/glm.hpp>

#include "global/Utils.h"


std::ostream & operator<<(std::ostream & cout, const glm::vec2 & vec)
{
    cout << vec.x << ' ' << vec.y;
    return cout;
}

