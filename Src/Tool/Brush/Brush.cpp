#include "Brush.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../Renderable/Widget/Canvas/Canvas.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../CutMullRom/CutMullRom.h"

void Brush::PaintOnPress(RenderTarget& data, RenderTarget& tmp, 
                         MouseContext mouse, Color color)
{
    drawing = true;
    start_pos = mouse.position;
}

void Brush::PaintOnMove(RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, Color color)
{
    if (drawing)
    {
        if (vertexes.size != 0 && vertexes[vertexes.End()].val == mouse.position)
            return;
        vertexes.PushBack(mouse.position);
        if (vertexes.size >= 5)
            vertexes.PopFront();
        
        DrawUsingCatMullRom(data, tmp, color, thickness, vertexes);
        last_pos = mouse.position;
    }
}

void Brush::PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, Color color)
{
    DrawTmpToData(data, tmp, color, thickness, vertexes);

    start_pos = Vec2(-1, -1);
    drawing   = false;
    vertexes.Clear();
}

void Brush::Disable(RenderTarget&  data,  RenderTarget& tmp, 
                    MouseContext mouse, Color         color)
{
    if (drawing)
    {
        DrawTmpToData(data, tmp, color, thickness, vertexes);

        start_pos = Vec2(1, -1);
        drawing   = false;
        vertexes.Clear();
    }
}

