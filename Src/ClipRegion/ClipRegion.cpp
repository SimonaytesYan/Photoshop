#include "ClipRegion.h"
#include "../RegionSet/RegionSet.h"
#include "../Useful.h"

ClipRegion::ClipRegion() :
nulled (false)
{
    x0 = 0;
    y0 = 0;
    x1 = 0;
    y1 = 0;
}

ClipRegion::ClipRegion(plugin::Vec2 _position, plugin::Vec2 _size, bool _nulled) :
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

ClipRegion::ClipRegion(const ClipRegion& a)
{
    x0 = a.x0;
    y0 = a.y0;
    x1 = a.x1;
    y1 = a.y1;

    nulled = a.nulled;
}


plugin::Vec2 ClipRegion::GetSize() const
{
    return plugin::Vec2(x1 - x0, y1 - y0);
}

plugin::Vec2 ClipRegion::GetPosition() const
{
    return plugin::Vec2(x0, y0);
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
    return a.x0 < x &&
           a.x1 > x;
}

inline bool YInsideRegion(ClipRegion a, double y)
{
    return a.y0 < y &&
           a.y1 > y;
}

bool ClipRegion::InsideP(plugin::Vec2 v) const
{
    return XInsideRegion(*this, v.GetX()) && YInsideRegion(*this, v.GetY());
}

void ClipRegion::Dump() const
{
    fprintf(stderr,  "{ ");
    GetPosition().Dump();
    fprintf(stderr, " ");
    (GetSize() + GetPosition()).Dump();
    fprintf(stderr, "}\n");
}

bool RegionIntersectP(ClipRegion a, ClipRegion b)
{
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
            if(a.x0 < a.x1 && b.y1 < a.y1)
                result.AddRegion(ClipRegion(a.x0, b.y1, a.x1, a.y1));

        if (YInsideRegion(a, b.y0))       //bottom region
            if(a.x0 < a.x1 && a.y0 < b.y0)
                result.AddRegion(ClipRegion(a.x0, a.y0, a.x1, b.y0));

        if (XInsideRegion(a, b.x0))       //left region
            if(a.x0 < b.x0 && max(a.y0, b.y0) < min(a.y1, b.y1))
                result.AddRegion(ClipRegion(a.x0, max(a.y0, b.y0), 
                                            b.x0, min(a.y1, b.y1)));

        if (XInsideRegion(a, b.x1))       //right region
            if(b.x1 < a.x1 && max(a.y0, b.y0) < min(a.y1, b.y1))
                result.AddRegion(ClipRegion(b.x1, max(a.y0, b.y0), 
                                            a.x1, min(a.y1, b.y1)));
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

