#include "LineTool.h"
#include "../../../RenderTarget/RenderTarget.h"
#include "../../../Useful.h"

void LineTool::CalcAndDrawShape(RenderTarget* target, plugin::MouseContext mouse, plugin::Color color)
{
    target->DrawLine(start_pos, mouse.position, color);
}
