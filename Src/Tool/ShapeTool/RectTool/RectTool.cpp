#include "RectTool.h"
#include "../../../RenderTarget/RenderTarget.h"
#include "../../../Useful.h"

void RectTool::CalcAndDrawShape(RenderTarget& target, MouseContext mouse, Color color)
{
    Vec2 position(min(start_pos.GetX(), mouse.position.GetX()),
                    min(start_pos.GetY(), mouse.position.GetY()));
    target.DrawRect(position, Vec2(abs((start_pos - mouse.position).GetX()), 
                                     abs((start_pos - mouse.position).GetY())),
                              color);
}
