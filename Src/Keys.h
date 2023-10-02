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
};
