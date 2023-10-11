#include "Vector/Vector.h"

enum Key
{
    a,
    b
};

enum MouseKey
{
    LEFT,
    RIGHT,
    MIDDLE
};

struct MouseCondition
{
    Vector   position;
    MouseKey key;

    MouseCondition() :
    position(Vector(0, 0)),
    key(LEFT)
    {};

    MouseCondition(Vector _position, MouseKey _key) : 
    position (_position),
    key (_key)
    {};
};
