#include "Brush.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"

void Brush::PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                    MouseCondition mouse, Color color)
{
    data.DrawCircle(mouse.position, r, color);
    drawing = true;
    start_pos = mouse.position;
}

void Brush::PaintOnMove(RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color)
{
    if (drawing)
    {
        data.DrawCircle(mouse.position, r, color);
        last_pos = mouse.position;
    }
}

void Brush::PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color)
{
    start_pos = Vector(-1, -1);
    drawing   = false;
}

void Brush::Disable()
{
    start_pos = Vector(1, -1);
}
