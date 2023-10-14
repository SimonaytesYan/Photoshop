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

ClipRegion::ClipRegion(Vector _position, Vector _size, bool _nulled) :
nulled    (_nulled)
{
    x0 = _position.GetX();
    y0 = _position.GetY();
    x1 = (_position + _size).GetX();
    y1 = (_position + _size).GetY();
}

ClipRegion::ClipRegion(double _x0, double _y0, double _x1, double _y1)
{
    x0 = _x0;
    y0 = _y0;
    x1 = _x1;
    y1 = _y1;
    nulled = false;
}


Vector ClipRegion::GetSize() const
{
    return Vector(x1 - x0, y1 - y0);
}

Vector ClipRegion::GetPosition() const
{
    return Vector(x0, y0);
}

bool operator==(ClipRegion a, ClipRegion b)
{
    return a.GetPosition() == b.GetPosition() && a.GetSize() == b.GetSize();
}

inline ClipRegion operator&&(ClipRegion a, ClipRegion b)
{
    double left_x   = max(a.x0, b.x0);
    double right_x  = min(a.x1, b.x1);

    double top_y    = max(a.y0, b.y0);
    double bottom_y = min(a.y1, b.y1);

    return ClipRegion(left_x, top_y, right_x, bottom_y);
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

//TODO переписать ClipRegion на 4 точки

bool RegionIntersectP(ClipRegion a, ClipRegion b)
{
    double a.x0 = a.GetPosition().GetX();
    double a.y0 = a.GetPosition().GetY();
    double a.x1 = a.GetPosition().GetX() + a.GetSize().GetX();
    double a.y1 = a.GetPosition().GetY() + a.GetSize().GetY();

    double b.x0 = b.GetPosition().GetX();
    double b.y0 = b.GetPosition().GetY();
    double b.x1 = b.GetPosition().GetX() + b.GetSize().GetX();
    double b.y1 = b.GetPosition().GetY() + b.GetSize().GetY();

    double X0 = max(a.x0, b.x0);
    double Y0 = max(a.y0, b.y0);
    double X1 = min(a.x1, b.x1);
    double Y1 = min(a.y1, b.y1);

    return (X0 < X1) && (Y0 < Y1);
}

RegionSet operator-(ClipRegion a, ClipRegion b)
{
    RegionSet result;

    if (a == b)
        return result;

    if (RegionIntersectP(a, b))
    {
        if (YInsideRegion(a, b.y1))       //up region
        {
            Vector position = Vector(a.x0, b.y1);
            Vector size     = Vector(a.size.GetX(), a.y1 - b.y1);
            if(a.x1 != 0 && a.y1 != 0)
                result.AddRegion(ClipRegion(a.x0, b.y1, a.x1, a.y1));
        }

        if (YInsideRegion(a, b.y0))       //bottom region
        {
            Vector position = a.position;
            Vector size     = Vector(a.size.GetX(), b.y0 - a.y0);
            if(size.GetX() != 0 && size.GetY() != 0)
                result.AddRegion(ClipRegion(position, size));
        }

        if (XInsideRegion(a, b.x0))       //left region
        {   
            Vector position(a.x0, max(a.y0, b.y0));
            Vector size    (b.x0 - a.x0, min(a.y1, b.y1) - max(a.y0, b.y0));

            if(size.GetX() != 0 && size.GetY() != 0)
                result.AddRegion(ClipRegion(position, size));
        }

        if (XInsideRegion(a, b.x1))       //right region
        {
            Vector position(b.x1, max(a.y0, b.y0));
            Vector size    (a.x1 - b.x1, min(a.y1, b.y1) - max(a.y0, b.y0));
            if(size.GetX() != 0 && size.GetY() != 0)
                result.AddRegion(ClipRegion(position, size));
        }
    }
    else
        result.AddRegion(ClipRegion(a));

    return result;
}

RegionSet operator||(ClipRegion a, ClipRegion b)
{
    RegionSet result = a - b;
    result.AddRegion(ClipRegion(b.GetPosition(), b.GetSize()));

    return result;
}

