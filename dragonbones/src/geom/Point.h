#ifndef DRAGONBONES_POINT_H
#define DRAGONBONES_POINT_H

#include "../core/DragonBones.h"

NAMESPACE_DRAGONBONES_BEGIN

class Point final
{
public:
    float x;
    float y;

    Point():
        x(0.f),
        y(0.f)
    {
    }
    Point(const Point& value)
    {
        operator=(value);
    }
    ~Point() {}

    inline void operator=(const Point& value)
    {
        x = value.x;
        y = value.y;
    }

    inline void clear()
    {
        x = y = 0.f;
    }
};

NAMESPACE_DRAGONBONES_END
#endif // DRAGONBONES_POINT_H