#include "ToolManager.h"
#include "../RenderTarget/RenderTarget.h"

void ToolManager::PaintOnPress(RenderTarget& data, RenderTarget& tmp, MouseContext mouse)
{
    if (tool != nullptr)
    {
        tool->PaintOnPress(data, tmp, mouse, color);
    }
}

void ToolManager::PaintOnMove(RenderTarget& data, RenderTarget& tmp, MouseContext mouse)
{   
    if (tool != nullptr)
    {
        tool->PaintOnMove(data, tmp, mouse, color);
    }
}

void ToolManager::PaintOnRelease(RenderTarget& data, RenderTarget& tmp, MouseContext mouse)
{
    if (tool != nullptr)
    {
        tool->PaintOnRelease(data, tmp, mouse, color);
    }
}

void ToolManager::DisableTool(RenderTarget& data, RenderTarget& tmp, MouseContext mouse)
{
    if (tool != nullptr)
        tool->Disable(data, tmp, mouse, color);
}

void ToolManager::ChangeTool(Tool* new_tool)
{
    tool = new_tool;
}

void ToolManager::ChangeColor(plugin::Color new_color)
{
    color = new_color;
}
