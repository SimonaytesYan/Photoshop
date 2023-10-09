#include <cmath>
#include <SFML/Graphics.hpp>

#include "Vector.h"

Vector::Vector(double _x, double _y) :
x (_x),
y (_y)
{}

Vector::~Vector()
{
    x = NAN;
    y = NAN;
}

void Vector::Dump()
{
    printf("(%.2lf, %.2lf)", x, y);
}

Vector operator+(const Vector& a, const Vector& b)
{
    Vector res = Vector(a.x + b.x, a.y + b.y);
    return res;
}

Vector operator-(const Vector& a)
{
    return Vector(-a.x, -a.y);
}

Vector operator-(const Vector& a, const Vector& b)
{
    return a + (-b);
}

Vector operator*(const Vector& a, double b)
{
    return Vector(a.x * b, a.y * b);
}

Vector operator/(const Vector& a, double b)
{
    return Vector(a.x / b, a.y / b);
}

double operator,(const Vector& a, const Vector& b)
{
    return a.x * b.x + a.y * b.y;
}

Vector operator!(const Vector& a)
{
    return Vector(a.x / a.Length(), a.y / a.Length());
}

Vector operator+(const Vector& a)
{
    return Vector(-a.y, a.x);
}

bool operator==(const Vector& a, const Vector& b)
{
    return a.x == b.x && a.y == b.y;
}

Vector operator^(const Vector& a, double b)
{
    Vector vec = a;
    vec.Rotate(-b);
    return vec;
}

void Vector::Rotate(double deg)
{
    double rad = M_PI / 180 * deg;

    double rot_x = cos(rad);
    double rot_y = sin(rad);

    double old_x = x;
    double old_y = y;
    x = old_x * rot_x - old_y * rot_y;
    y = old_y * rot_x + old_x * rot_y;
}

double Vector::Length() const
{
    return sqrt(x*x + y*y);
}
