#include "Brush.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../Renderable/Widget/Canvas/Canvas.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../CutMullRom/CutMullRom.h"

void Brush::paintOnPress(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                         MouseContext mouse, plugin::Color color)
{
    drawing = true;
    start_pos = mouse.position;
}

void Brush::paintOnMove(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color color)
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

void Brush::paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color color)
{
    DrawTmpToData(data, tmp, color, thickness, vertexes);

    start_pos = plugin::Vec2(-1, -1);
    drawing   = false;
    vertexes.Clear();
}

void Brush::disable(plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                    MouseContext mouse, plugin::Color         color)
{
    if (drawing)
    {
        DrawTmpToData(data, tmp, color, thickness, vertexes);

        start_pos = plugin::Vec2(1, -1);
        drawing   = false;
        vertexes.Clear();
    }
}

