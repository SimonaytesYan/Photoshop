#include "CircleTool.h"
#include "../../../RenderTarget/RenderTarget.h"
#include "../../../Useful.h"

void CircleTool::CalcAndDrawShape(RenderTarget* target, MouseContext mouse, plugin::Color color)
{
    plugin::Vec2 position(min(start_pos.GetX(), mouse.position.GetX()),
                    min(start_pos.GetY(), mouse.position.GetY()));

    double x_len = abs((start_pos - mouse.position).GetX());
    double y_len = abs((start_pos - mouse.position).GetY());
    if (x_len < y_len)
        target->DrawCircle(position, 
                          thickness + y_len/2, 
                          color,
                          plugin::Vec2(x_len/y_len, 1));
    else if (x_len > y_len)
        target->DrawCircle(position, 
                          thickness + x_len/2, 
                          color,
                          plugin::Vec2(1, y_len/x_len));
    else if (x_len == y_len)
        target->DrawCircle(position, 
                           thickness + x_len/2, 
                           color,
                           plugin::Vec2(1, 1));
}
