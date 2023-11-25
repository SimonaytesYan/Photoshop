#include "SplineTool.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../Renderable/Widget/Canvas/Canvas.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../Useful.h"
#include "../../CutMullRom/CutMullRom.h"

void SplineTool::disable(plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                         plugin::MouseContext mouse, plugin::Color         color)
{
    DrawTmpToData(data, tmp, color, thickness, vertexes);
    vertexes.Clear();
    drawing = false;
}

void SplineTool::paintOnPress(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color)
{
    if (mouse.key == plugin::MouseButton::Left)
    {
        if (vertexes.size != 0 && vertexes[vertexes.End()].val == mouse.position)
            return;
        vertexes.PushBack(mouse.position);
        if (vertexes.size >= 5)
            vertexes.PopFront();
        
        DrawUsingCatMullRom(data, tmp, color, thickness, vertexes);
        drawing = true;
    }
    else
    {
        if (drawing)
        {
            DrawTmpToData(data, tmp, color, thickness, vertexes);
            vertexes.Clear();
            drawing   = false;
        }
    }
}  
