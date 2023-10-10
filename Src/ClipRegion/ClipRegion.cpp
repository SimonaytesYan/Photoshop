#include "ClipRegion.h"
#include "../RegionSet/RegionSet.h"

inline double max(double a, double b)
{
    return a < b ? b : a;
}

inline double min(double a, double b)
{
    return a < b ? a : b;
}

ClipRegion::ClipRegion(Vector _position, Vector _size, Color _color) :
position (_position),
size     (_size),
color    (_color)
{}

Color ClipRegion::GetColor() const
{
    return color;
}

Vector ClipRegion::GetSize() const
{
    return size;
}

Vector ClipRegion::GetPosition() const
{
    return position;
}

bool operator==(ClipRegion a, ClipRegion b)
{
    return a.GetPosition() == b.GetPosition() && a.GetSize() == b.GetSize();
}

inline ClipRegion operator&&(ClipRegion a, ClipRegion b)
{
    double left_x   = max(a.position.GetX(), b.position.GetX());
    double right_x  = min(a.position.GetX() + a.size.GetX(), 
                          b.position.GetX() + b.size.GetX());

    double top_y    = max(a.position.GetY(), b.position.GetY());
    double bottom_y = min(a.position.GetY() + a.size.GetY(),
                          b.position.GetY() + b.size.GetY());

    Vector position(left_x, top_y);
    Vector size = Vector(right_x, bottom_y) - position;

    Color res_color = Color((a.color.r + b.color.r) / 2, 
                            (a.color.g + b.color.g) / 2, 
                            (a.color.b + b.color.b) / 2);

    return ClipRegion(position, size, res_color);
}

inline bool XInsideRegion(ClipRegion a, double x)
{
    return a.GetPosition().GetX() < x &&
           ((a.GetPosition() + a.GetSize()).GetX() > x);
}

inline bool YInsideRegion(ClipRegion a, double y)
{
    return a.GetPosition().GetY() < y &&
           ((a.GetPosition() + a.GetSize()).GetY() > y);
}

void ClipRegion::Dump() const
{
    printf("{ ");
    GetPosition().Dump();
    printf(" ");
    (GetSize() + GetPosition()).Dump();
    printf("}\n");
}

bool RegionIntersectP(ClipRegion a, ClipRegion b)
{
    double a_x0 = a.GetPosition().GetX();
    double a_y0 = a.GetPosition().GetY();
    double a_x1 = a.GetPosition().GetX() + a.GetSize().GetX();
    double a_y1 = a.GetPosition().GetY() + a.GetSize().GetY();

    double b_x0 = b.GetPosition().GetX();
    double b_y0 = b.GetPosition().GetY();
    double b_x1 = b.GetPosition().GetX() + b.GetSize().GetX();
    double b_y1 = b.GetPosition().GetY() + b.GetSize().GetY();

    double X0 = max(a_x0, b_x0);
    double Y0 = max(a_y0, b_y0);
    double X1 = min(a_x1, b_x1);
    double Y1 = min(a_y1, b_y1);

    return (X0 < X1) && (Y0 < Y1);
}

RegionSet operator-(ClipRegion a, ClipRegion b)
{
    RegionSet result;

    if (a == b)
    {
        return result;
    }

    double a_x0 = a.GetPosition().GetX();
    double a_y0 = a.GetPosition().GetY();
    double a_x1 = a.GetPosition().GetX() + a.GetSize().GetX();
    double a_y1 = a.GetPosition().GetY() + a.GetSize().GetY();

    double b_x0 = b.GetPosition().GetX();
    double b_y0 = b.GetPosition().GetY();
    double b_x1 = b.GetPosition().GetX() + b.GetSize().GetX();
    double b_y1 = b.GetPosition().GetY() + b.GetSize().GetY();

    #ifdef DEBUG
        printf("a = ");
        a.Dump();
        printf("b = ");
        b.Dump();
    #endif

    if (RegionIntersectP(a, b))
    {
        if (YInsideRegion(a, b_y1))       //up region
        {
            Vector position = Vector(a_x0, b_y1);
            Vector size     = Vector(a.size.GetX(), a_y1 - b_y1);
            if(size.GetX() != 0 && size.GetY() != 0)
                result.AddRegion(ClipRegion(position, size));

            #ifdef DEBUG
                printf("0 rect = ");
                ClipRegion(position, size).Dump();
            #endif
        }

        if (YInsideRegion(a, b_y0))       //bottom region
        {
            Vector position = a.position;
            Vector size     = Vector(a.size.GetX(), b_y0 - a_y0);
            if(size.GetX() != 0 && size.GetY() != 0)
                result.AddRegion(ClipRegion(position, size));

            #ifdef DEBUG
                printf("1 rect = ");
                ClipRegion(position, size).Dump();
            #endif
        }

        if (XInsideRegion(a, b_x0))       //left region
        {   
            Vector position(a_x0, max(a_y0, b_y0));
            Vector size    (b_x0 - a_x0, min(a_y1, b_y1) - max(a_y0, b_y0));

            if(size.GetX() != 0 && size.GetY() != 0)
                result.AddRegion(ClipRegion(position, size));

            #ifdef DEBUG
                printf("2 rect = ");
                ClipRegion(position, size).Dump();
            #endif
        }

        if (XInsideRegion(a, b_x1))       //right region
        {
            Vector position(b_x1, max(a_y0, b_y0));
            Vector size    (a_x1 - b_x1, min(a_y1, b_y1) - max(a_y0, b_y0));
            if(size.GetX() != 0 && size.GetY() != 0)
                result.AddRegion(ClipRegion(position, size));

            #ifdef DEBUG
                printf("3 rect = ");
                ClipRegion(position, size).Dump();
            #endif
        }
    }
    else
    {
        result.AddRegion(ClipRegion(a));
        #ifdef DEBUG
            printf("4 rect = ");
            a.Dump();
        #endif
    }

    return result;
}

RegionSet operator||(ClipRegion a, ClipRegion b)
{
    RegionSet result = a - b;
    result.AddRegion(ClipRegion(a.GetPosition(), a.GetSize()));

    return result;
}

