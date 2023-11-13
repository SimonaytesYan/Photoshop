#include <cmath>
#include <SFML/Graphics.hpp>

#include "Vec2.h"

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(double _x, double _y) :
x (_x),
y (_y)
{}

Vec2::~Vec2()
{
    x = NAN;
    y = NAN;
}

void Vec2::Dump()
{
    fprintf(stderr, "(%.2lf, %.2lf)", x, y);
}

Vec2 Vec2::operator=(VectorI v)
{
    x = v.x;
    y = v.y;

    return *this;
}

VectorI operator+(const VectorI& a, const VectorI& b)
{
    return VectorI(a.x + b.x, a.y + b.y);
}

Vec2 operator+(const Vec2& a, const Vec2& b)
{
    Vec2 res = Vec2(a.x + b.x, a.y + b.y);
    return res;
}

Vec2 operator-(const Vec2& a)
{
    return Vec2(-a.x, -a.y);
}

Vec2 operator-(const Vec2& a, const Vec2& b)
{
    return a + (-b);
}

Vec2 operator*(const Vec2& a, double b)
{
    return Vec2(a.x * b, a.y * b);
}

Vec2 operator*(double a, const Vec2& b)
{
    return Vec2(b.x * a, b.y * a);
}

Vec2 operator/(const Vec2& a, double b)
{
    return Vec2(a.x / b, a.y / b);
}

double operator,(const Vec2& a, const Vec2& b)
{
    return a.x * b.x + a.y * b.y;
}

Vec2 operator!(const Vec2& a)
{
    return Vec2(a.x / a.Length(), a.y / a.Length());
}

Vec2 operator+(const Vec2& a)
{
    return Vec2(-a.y, a.x);
}

bool operator==(const Vec2& a, const Vec2& b)
{
    return a.x == b.x && a.y == b.y;
}

Vec2 operator^(const Vec2& a, double b)
{
    Vec2 vec = a;
    vec.Rotate(-b);
    return vec;
}

void Vec2::Rotate(double deg)
{
    double rad = M_PI / 180 * deg;

    double rot_x = cos(rad);
    double rot_y = sin(rad);

    double old_x = x;
    double old_y = y;
    x = old_x * rot_x - old_y * rot_y;
    y = old_y * rot_x + old_x * rot_y;
}

double Vec2::Length() const
{
    return sqrt(x*x + y*y);
}
