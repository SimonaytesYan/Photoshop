#include "PolylineTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../Useful.h"

void PolylineTool::CalcAndDrawPolyline(plugin::RenderTargetI* target, 
                                       plugin::MouseContext mouse, plugin::Color color)
{
    for (int i = vertexes.GetLength() - 1; i >= 1; i--)
        target->drawLine(vertexes[i], vertexes[i - 1], color);
}

void PolylineTool::disable(plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                           plugin::MouseContext mouse, plugin::Color         color)
{
    ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
    CalcAndDrawPolyline(data, mouse, color);
        
    vertexes.Clear();
    start_pos = plugin::Vec2(1, -1);
    drawing   = false;
}

void PolylineTool::paintOnPress(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color)
{
    if (mouse.button == plugin::MouseButton::Right)
    {
        if (drawing)
        {
            ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
            CalcAndDrawPolyline(data, mouse, color);
            
            vertexes.Clear();
            drawing   = false;
        }
    }
    else
    {
        vertexes.PushBack(mouse.position);
        ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
        CalcAndDrawPolyline(data, mouse, color);
        
        drawing = true;
    }
}

void PolylineTool::paintOnMove(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                               plugin::MouseContext mouse, plugin::Color color)
{
    if (drawing)
    {
        ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));

        vertexes.PushBack(mouse.position);
        CalcAndDrawPolyline(tmp, mouse, color);
        vertexes.PopBack();
    }
}
