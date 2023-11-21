#include "ShapeTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"

void ShapeTool::paintOnPress  (plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color)
{
    tmp.clear(plugin::Color(0, 0, 0, 0));
    start_pos = mouse.position;
    CalcAndDrawShape(tmp, mouse, color);
    drawing = true;
}

void ShapeTool::paintOnMove(plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                             MouseContext mouse, plugin::Color color)
{
    if (drawing)
    {
        tmp.clear(plugin::Color(0, 0, 0, 0));
        CalcAndDrawShape(tmp, mouse, color);
        last_pos = mouse.position;
    }
}

void ShapeTool::paintOnRelease(plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color)
{
    if (drawing)
    {
        tmp.clear(plugin::Color(0, 0, 0, 0));
        CalcAndDrawShape(data, mouse, color);
        start_pos = plugin::Vec2(-1, -1);
        drawing   = false;
    }
}

void ShapeTool::disable(RenderTarget&  data,  plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color         color)
{
    if (drawing)
    {
        tmp.clear(plugin::Color(0, 0, 0, 0));
        CalcAndDrawShape(data, mouse, color);
        
        start_pos = plugin::Vec2(-1, -1);
        drawing   = false;
    }
}
