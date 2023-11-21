#include "ShapeTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"

void ShapeTool::paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color)
{
    ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
    start_pos = mouse.position;
    CalcAndDrawShape((RenderTarget*)tmp, mouse, color);
    drawing = true;
}

void ShapeTool::paintOnMove(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                             MouseContext mouse, plugin::Color color)
{
    if (drawing)
    {
        ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
        CalcAndDrawShape((RenderTarget*)tmp, mouse, color);
        last_pos = mouse.position;
    }
}

void ShapeTool::paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color)
{
    if (drawing)
    {
        ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
        CalcAndDrawShape((RenderTarget*)data, mouse, color);
        start_pos = plugin::Vec2(-1, -1);
        drawing   = false;
    }
}

void ShapeTool::disable(plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color         color)
{
    if (drawing)
    {
        ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
        CalcAndDrawShape((RenderTarget*)data, mouse, color);
        
        start_pos = plugin::Vec2(-1, -1);
        drawing   = false;
    }
}
