#ifndef SYM_GEOM_VECTOR
#define SYM_GEOM_VECTOR

#include <math.h>

class Vector
{
    double x;
    double y;

public : 
    Vector(double x, double y);
    ~Vector();

    double    GetX    () {return x;};
    double    GetY    () {return y;};

    void   Dump  ();
    void   Rotate(double deg);
    double Length() const;

    friend Vector operator+(const Vector& a, const Vector& b);
    friend Vector operator-(const Vector& a);
    friend Vector operator-(const Vector& a, const Vector& b);
    friend Vector operator*(const Vector& a, double b);
    friend Vector operator/(const Vector& a, double b);
    friend double operator,(const Vector& a, const Vector& b);  
    friend Vector operator!(const Vector& a);
    friend Vector operator+(const Vector& a);
    friend Vector operator^(const Vector& a, double b);
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a);
Vector operator-(const Vector& a, const Vector& b);
Vector operator*(const Vector& a, double b);
Vector operator/(const Vector& a, double b);
double operator,(const Vector& a, const Vector& b);		//scalar product
Vector operator!(const Vector& a);						//return normalized vector
Vector operator+(const Vector& a);						//return normal to vector
Vector operator^(const Vector& a, double b);            //rotate a by b degrees clockwise

#endif //SYM_GEOM_VECTOR
