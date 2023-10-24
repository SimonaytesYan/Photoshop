#include "PolylineTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../Useful.h"

void PolylineTool::CalcAndDrawPolyline(RenderTarget& target, MouseCondition mouse, Color color)
{
    for (int i = vertexes.GetLength() - 1; i >= 1; i--)
        target.DrawLine(vertexes[i], vertexes[i - 1], color);
}

void PolylineTool::Disable(RenderTarget&  data,  RenderTarget& tmp, 
                           MouseCondition mouse, Color         color)
{
    tmp.Clear(Color(0, 0, 0, 0));
    CalcAndDrawPolyline(data, mouse, color);
        
    vertexes.Clear();
    start_pos = Vector(1, -1);
    drawing   = false;
}

void PolylineTool::PaintOnPress(RenderTarget& data, RenderTarget& tmp, 
                                MouseCondition mouse, Color color)
{
    if (mouse.key == RIGHT)
    {
        if (drawing)
        {
            tmp.Clear(Color(0, 0, 0, 0));
            CalcAndDrawPolyline(data, mouse, color);
            
            vertexes.Clear();
            drawing   = false;
        }
    }
    else
    {
        vertexes.PushBack(mouse.position);
        tmp.Clear(Color(0, 0, 0, 0));
        CalcAndDrawPolyline(data, mouse, color);
        
        drawing = true;
    }
}

void PolylineTool::PaintOnMove(RenderTarget& data, RenderTarget& tmp, 
                               MouseCondition mouse, Color color)
{
    if (drawing)
    {
        tmp.Clear(Color(0, 0, 0, 0));

        vertexes.PushBack(mouse.position);
        CalcAndDrawPolyline(tmp, mouse, color);
        vertexes.PopBack();
    }
}
