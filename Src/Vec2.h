#ifndef SYM_GEOM_VECTOR
#define SYM_GEOM_VECTOR

#include <math.h>
#include "Standart/Standart.h"

struct VectorI
{
    int x;
    int y;

    VectorI()
    {
        x = 0;
        y = 0;
    }

    VectorI(int _x, int _y) : 
    x(_x), 
    y(_y)
    {}

    VectorI(plugin::Vec2 v)
    {
        x = v.GetX();
        y = v.GetY();
    }

    VectorI operator=(plugin::Vec2 v)
    {
        x = v.GetX();
        y = v.GetY();

        return *this;
    }    
};

static VectorI operator+(const VectorI& a, const VectorI& b)
{
    return VectorI(a.x + b.x, a.y + b.y);
}

#endif //SYM_GEOM_VECTOR
