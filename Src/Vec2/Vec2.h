#ifndef SYM_GEOM_VECTOR
#define SYM_GEOM_VECTOR

#include <math.h>

namespace plugin
{
    struct VectorI;

    struct Vec2
    {
        double x;
        double y;

    public : 
        Vec2();
        Vec2(double _x, double _y);
        ~Vec2();

        double    GetX    () {return x;};
        double    GetY    () {return y;};

        void   Dump  ();
        void   Rotate(double deg);
        double Length() const;

        Vec2 operator=(VectorI v);

        friend Vec2 operator+(const Vec2& a, const Vec2& b);
        friend Vec2 operator-(const Vec2& a);
        friend Vec2 operator-(const Vec2& a, const Vec2& b);
        friend Vec2 operator*(const Vec2& a, double b);
        friend Vec2 operator*(double a, const Vec2& b);
        friend Vec2 operator/(const Vec2& a, double b);
        friend double operator,(const Vec2& a, const Vec2& b);  
        friend Vec2 operator!(const Vec2& a);
        friend Vec2 operator+(const Vec2& a);
        friend Vec2 operator^(const Vec2& a, double b);
        friend bool   operator==(const Vec2& a, const Vec2& b);
    };

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

        VectorI(Vec2 v)
        {
            x = v.GetX();
            y = v.GetY();
        }

        VectorI operator=(Vec2 v)
        {
            x = v.GetX();
            y = v.GetY();

            return *this;
        }

        friend VectorI operator+(const VectorI& a, const VectorI& b);
    };

    Vec2 operator+(const Vec2& a, const Vec2& b);
    Vec2 operator-(const Vec2& a);
    Vec2 operator-(const Vec2& a, const Vec2& b);
    Vec2 operator*(const Vec2& a, double b);
    Vec2 operator/(const Vec2& a, double b);
    bool   operator==(const Vec2& a, const Vec2& b);
    double operator,(const Vec2& a, const Vec2& b);		//scalar product
    Vec2 operator!(const Vec2& a);						//return normalized vector
    Vec2 operator+(const Vec2& a);						//return normal to vector
    Vec2 operator^(const Vec2& a, double b);            //rotate a by b degrees clockwise
}


#endif //SYM_GEOM_VECTOR