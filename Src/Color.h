#ifndef SYM_COLOR
#define SYM_COLOR

#include <SFML/Graphics.hpp>

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    Color() :
    r (0),
    g (0),
    b (0),
    a (255)
    {};
    
    Color(unsigned char _r, 
          unsigned char _g, 
          unsigned char _b, 
          unsigned char _a = 255) :
    r (_r),
    g (_g),
    b (_b),
    a (_a)
    {};

    Color Inverse()
    {
        return Color(255 - r, 255 - g, 255 - b);
    };
};

static bool operator==(Color a, Color b)
{
    return a.a == b.a &&
           a.r == b.r &&
           a.g == b.g &&
           a.b == b.b;
}

#endif //SYM_COLOR