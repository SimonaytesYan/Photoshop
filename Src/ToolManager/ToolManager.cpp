#include "ToolManager.h"
#include "../RenderTarget/RenderTarget.h"

void ToolManager::paintOnPress(plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, MouseContext mouse)
{
    if (tool != nullptr)
    {
        tool->paintOnPress(data, tmp, mouse, color);
    }
}

void ToolManager::paintOnMove(plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, MouseContext mouse)
{   
    if (tool != nullptr)
    {
        tool->paintOnMove(data, tmp, mouse, color);
    }
}

void ToolManager::paintOnRelease(plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, MouseContext mouse)
{
    if (tool != nullptr)
    {
        tool->paintOnRelease(data, tmp, mouse, color);
    }
}

void ToolManager::disableTool(plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, MouseContext mouse)
{
    if (tool != nullptr)
        tool->disable(data, tmp, mouse, color);
}

void ToolManager::ChangeTool(Tool* new_tool)
{
    tool = new_tool;
}

void ToolManager::ChangeColor(plugin::Color new_color)
{
    color = new_color;
}
