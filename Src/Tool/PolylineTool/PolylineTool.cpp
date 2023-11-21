#include "PolylineTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../Useful.h"

void PolylineTool::CalcAndDrawPolyline(RenderTarget& target, MouseContext mouse, plugin::Color color)
{
    for (int i = vertexes.GetLength() - 1; i >= 1; i--)
        target.DrawLine(vertexes[i], vertexes[i - 1], color);
}

void PolylineTool::disable(RenderTarget&  data,  plugin::RenderTargetI* tmp, 
                           MouseContext mouse, plugin::Color         color)
{
    tmp.clear(plugin::Color(0, 0, 0, 0));
    CalcAndDrawPolyline(data, mouse, color);
        
    vertexes.Clear();
    start_pos = plugin::Vec2(1, -1);
    drawing   = false;
}

void PolylineTool::paintOnPress(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color)
{
    if (mouse.key == MouseButton::Right)
    {
        if (drawing)
        {
            tmp.clear(plugin::Color(0, 0, 0, 0));
            CalcAndDrawPolyline(data, mouse, color);
            
            vertexes.Clear();
            drawing   = false;
        }
    }
    else
    {
        vertexes.PushBack(mouse.position);
        tmp.clear(plugin::Color(0, 0, 0, 0));
        CalcAndDrawPolyline(data, mouse, color);
        
        drawing = true;
    }
}

void PolylineTool::paintOnMove(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                               MouseContext mouse, plugin::Color color)
{
    if (drawing)
    {
        tmp.clear(plugin::Color(0, 0, 0, 0));

        vertexes.PushBack(mouse.position);
        CalcAndDrawPolyline(tmp, mouse, color);
        vertexes.PopBack();
    }
}
