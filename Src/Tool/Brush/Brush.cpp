#include "Brush.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../Renderable/Widget/Canvas/Canvas.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../CutMullRom/CutMullRom.h"

void Brush::PaintOnPress(RenderTarget& data, RenderTarget& tmp, 
                         MouseCondition mouse, Color color)
{
    drawing = true;
    start_pos = mouse.position;
}

void Brush::PaintOnMove(RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color)
{
    if (drawing)
    {
        vertexes.PushBack(mouse.position);
        if (vertexes.size >= 5)
            vertexes.PopFront();
        
        DrawUsingCatMullRom(data, tmp, color, thickness, vertexes);
        last_pos = mouse.position;
    }
}

void Brush::PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color)
{
    DrawTmpToData(data, tmp, color, thickness, vertexes);

    start_pos = Vector(-1, -1);
    vertexes.Clear();
    drawing   = false;
}

void Brush::Disable()
{
    start_pos = Vector(1, -1);
    drawing   = false;
    vertexes.Clear();
}

