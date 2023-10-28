#ifndef SYM_KEYS
#define SYM_KEYS

#include "Vector/Vector.h"

enum Key
{
    A,    // The A key
    B,    // The B key
    C,    // The C key
    D,    // The D key
    E,    // The E key
    F,    // The F key
    G,    // The G key
    H,    // The H key
    I,    // The I key
    J,    // The J key
    K,    // The K key
    L,    // The L key
    M,    // The M key
    N,    // The N key
    O,    // The O key
    P,    // The P key
    Q,    // The Q key
    R,    // The R key
    S,    // The S key
    T,    // The T key
    U,    // The U key
    V,    // The V key
    W,    // The W key
    X,    // The X key
    Y,    // The Y key
    Z,    // The Z key
    Num0, // The 0 key
    Num1, // The 1 key
    Num2, // The 2 key
    Num3, // The 3 key
    Num4, // The 4 key
    Num5, // The 5 key
    Num6, // The 6 key
    Num7, // The 7 key
    Num8, // The 8 key
    Num9, // The 9 key

    Comma  = 49,        ///< The , key
    Period = 50,       ///< The . key
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

#endif //SYM_KEYS
