#include "ShapeTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"

void ShapeTool::PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                                MouseCondition mouse, Color color)
{
    tmp.Clear(Color(0, 0, 0, 0));
    start_pos = mouse.position;
    CalcAndDrawShape(tmp, mouse, color);
    drawing = true;
}

void ShapeTool::PaintOnMove(RenderTarget& data, RenderTarget& tmp, 
                             MouseCondition mouse, Color color)
{
    if (drawing)
    {
        tmp.Clear(Color(0, 0, 0, 0));
        CalcAndDrawShape(tmp, mouse, color);
        last_pos = mouse.position;
    }
}

void ShapeTool::PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                                MouseCondition mouse, Color color)
{
    if (drawing)
    {
        tmp.Clear(Color(0, 0, 0, 0));
        CalcAndDrawShape(data, mouse, color);
        start_pos = Vector(-1, -1);
        drawing   = false;
    }
}

void ShapeTool::Disable()
{
    start_pos = Vector(1, -1);
}
