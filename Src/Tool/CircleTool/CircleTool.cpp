#include "CircleTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"

double min(double a, double b)
{
    return a < b ? a : b;
}

void CircleTool::PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                    MouseCondition mouse, Color color)
{
    tmp.Clear(Color(0, 0, 0, 0));
    tmp.DrawCircle(mouse.position, thickness, color);
    drawing = true;
    start_pos = mouse.position;
}

void CircleTool::CulcAndDrawCircle(RenderTarget& target, MouseCondition mouse, Color color)
{
    Vector position(min(start_pos.GetX(), mouse.position.GetX()),
                    min(start_pos.GetY(), mouse.position.GetY()));
    target.DrawCircle(position, 
                      thickness + (last_pos - start_pos).Length()/2, 
                      color);
}

void CircleTool::PaintOnMove(RenderTarget& data, RenderTarget& tmp, 
                             MouseCondition mouse, Color color)
{
    if (drawing)
    {
        tmp.Clear(Color(0, 0, 0, 0));
        CulcAndDrawCircle(tmp, mouse, color);
        last_pos = mouse.position;
    }
}

void CircleTool::PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                                MouseCondition mouse, Color color)
{
    if (drawing)
    {
        tmp.Clear(Color(0, 0, 0, 0));
        CulcAndDrawCircle(data, mouse, color);
        start_pos = Vector(-1, -1);
        drawing   = false;
    }
}

void CircleTool::Disable()
{
    start_pos = Vector(1, -1);
}
