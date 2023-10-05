#include "ClipRegion.h"
//#include "../RegionSet/RegionSet.h"

double max(double a, double b)
{
    return a < b ? b : a;
}

double min(double a, double b)
{
    return a < b ? a : b;
}

ClipRegion::ClipRegion(Vector _position, Vector _size, Color _color) :
position (_position),
size     (_size),
color    (_color)
{
}

Vector ClipRegion::GetSize()
{
    return size;
}

Vector ClipRegion::GetPosition()
{
    return position;
}

ClipRegion operator&&(ClipRegion a, ClipRegion b)
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

bool XInsideRegion(ClipRegion a, double x)
{
    return a.GetPosition().GetX() < x &&
           a.GetPosition().GetX() + a.GetSize().GetX() > x;
}

bool YInsideRegion(ClipRegion a, double y)
{
    return a.GetPosition().GetY() < y &&
           a.GetPosition().GetY() + a.GetSize().GetY() > y;
}

RegionSet operator/(ClipRegion a, ClipRegion b)
{
    RegionSet result;

    double a_x0 = a.GetPosition().GetX();
    double a_y0 = a.GetPosition().GetY();
    double a_x1 = a.GetPosition().GetX() + a.GetSize().GetX();
    double a_y1 = a.GetPosition().GetY() + a.GetSize().GetY();

    double b_x0 = b.GetPosition().GetX();
    double b_y0 = b.GetPosition().GetY();
    double b_x1 = b.GetPosition().GetX() + b.GetSize().GetX();
    double b_y1 = b.GetPosition().GetY() + b.GetSize().GetY();

    if (YInsideRegion(a, b_y0) &&
        (XInsideRegion(a, b_x0) || 
         XInsideRegion(a, b_x1)))       //up region
    {
        result.AddRegion(new ClipRegion(a.position, 
                                        Vector(a.size.GetX(), b_y0 - a_y0)));
    }

    if (YInsideRegion(a, b_y1) &&
        (XInsideRegion(a, b_x0) ||
         XInsideRegion(a, b_x1)))       //bottom region
    {
        result.AddRegion(new ClipRegion(Vector(a_x0, b_y1), 
                                        Vector(a.size.GetX(), a_y1 - b_y1)));
    }

    if (XInsideRegion(a, b_x0) &&
        (YInsideRegion(a, b_y0) ||
         YInsideRegion(a, b_y1)))       //left region
    {   
        Vector position(a_x0, max(a_y0, b_y0));
        Vector size    (b_x0 - a_x0, b_y1 - max(a_y0, b_y0));
        result.AddRegion(new ClipRegion(position, size));
    }
                        
    if (XInsideRegion(a, b_x0) &&
        (YInsideRegion(a, b_y0) ||
         YInsideRegion(a, b_y1)))
    {
        Vector position(b_x1, max(a_y0, b_y0));
        Vector size    (a_x1 - b_x1, b_y1 - max(a_y0, b_y0));
        result.AddRegion(new ClipRegion(position, size));
    }

    return result;
}

RegionSet operator||(ClipRegion a, ClipRegion b)
{
    RegionSet result = a / b;
    result.AddRegion(new ClipRegion(a.GetPosition(), a.GetSize()));

    return result;
}

