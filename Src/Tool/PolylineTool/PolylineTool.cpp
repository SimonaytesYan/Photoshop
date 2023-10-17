#include "PolylineTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../Useful.h"

void PolylineTool::CalcAndDrawPolyline(RenderTarget& target, MouseCondition mouse, Color color)
{
    for (int i = vertexes.GetLength() - 1; i >= 1; i--)
        target.DrawLine(vertexes[i], vertexes[i - 1], color);
}

void PolylineTool::Disable()
{
    vertexes.Clear();
    start_pos = Vector(1, -1);
}

void PolylineTool::PaintOnPress(RenderTarget& data, RenderTarget& tmp, 
                                MouseCondition mouse, Color color)
{
    tmp.Clear(Color(0, 0, 0, 0));
    start_pos = mouse.position;
    vertexes.PushBack(mouse.position);
    CalcAndDrawPolyline(tmp, mouse, color);
    drawing = true;
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

void PolylineTool::PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                                  MouseCondition mouse, Color color)
{
    if (mouse.key == RIGHT)
    {
        if (drawing)
        {
            tmp.Clear(Color(0, 0, 0, 0));
            vertexes.PopBack();
            CalcAndDrawPolyline(data, mouse, color);
            
            vertexes.Clear();
            start_pos = Vector(-1, -1);
            drawing   = false;
        }
    }
    else
    {
        if (drawing)
        {
            vertexes.PushBack(mouse.position);
            tmp.Clear(Color(0, 0, 0, 0));
            CalcAndDrawPolyline(tmp, mouse, color);
        }
    }
}