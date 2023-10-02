#include <cmath>
#include <SFML/Graphics.hpp>

#include "Vector.h"

Vector::Vector(double x, double y, sf::Color color) :
x (x),
y (y),
color (color)
{}

Vector::~Vector()
{
    x = NAN;
    y = NAN;
}

void Vector::Dump()
{
    fprintf(stderr, "(%lf, %lf)\n", x, y);
}

Vector operator+(const Vector& a, const Vector& b)
{
    sf::Color new_color((a.color.r + b.color.r)/2, 
                        (a.color.g + b.color.g)/2,
                        (a.color.b + b.color.b)/2);

    Vector res = Vector(a.x + b.x, a.y + b.y, new_color);
    return res;
}

Vector operator-(const Vector& a)
{
    sf::Color new_color(255 - a.color.r, 
                        255 - a.color.g, 
                        255 - a.color.b);
    return Vector(-a.x, -a.y, new_color);
}

Vector operator-(const Vector& a, const Vector& b)
{
    return a + (-b);
}

Vector operator*(const Vector& a, double b)
{
    return Vector(a.x * b, a.y * b, a.color);
}

Vector operator/(const Vector& a, double b)
{
    return Vector(a.x / b, a.y / b, a.color);
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
    sf::Color new_color(255 - a.color.r, 
                        255 - a.color.g, 
                        255 - a.color.b);
    return Vector(-a.y, a.x, new_color);
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
