#ifndef SYM_GEOM_VECTOR
#define SYM_GEOM_VECTOR

#include <math.h>

struct VectorI;

class Vector
{
    double x;
    double y;

public : 
    Vector(double _x, double _y);
    ~Vector();

    double    GetX    () {return x;};
    double    GetY    () {return y;};

    void   Dump  ();
    void   Rotate(double deg);
    double Length() const;

    Vector operator=(VectorI v);

    friend Vector operator+(const Vector& a, const Vector& b);
    friend Vector operator-(const Vector& a);
    friend Vector operator-(const Vector& a, const Vector& b);
    friend Vector operator*(const Vector& a, double b);
    friend Vector operator/(const Vector& a, double b);
    friend double operator,(const Vector& a, const Vector& b);  
    friend Vector operator!(const Vector& a);
    friend Vector operator+(const Vector& a);
    friend Vector operator^(const Vector& a, double b);
    friend bool   operator==(const Vector& a, const Vector& b);
};

struct VectorI
{
    int x;
    int y;

    VectorI(int _x, int _y) : 
    x(_x), 
    y(_y)
    {}

    VectorI(Vector v)
    {
        x = v.GetX();
        y = v.GetY();
    }

    VectorI operator=(Vector v)
    {
        x = v.GetX();
        y = v.GetY();

        return *this;
    }

    friend VectorI operator+(const VectorI& a, const VectorI& b);
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a);
Vector operator-(const Vector& a, const Vector& b);
Vector operator*(const Vector& a, double b);
Vector operator/(const Vector& a, double b);
bool   operator==(const Vector& a, const Vector& b);
double operator,(const Vector& a, const Vector& b);		//scalar product
Vector operator!(const Vector& a);						//return normalized vector
Vector operator+(const Vector& a);						//return normal to vector
Vector operator^(const Vector& a, double b);            //rotate a by b degrees clockwise

#endif //SYM_GEOM_VECTOR
