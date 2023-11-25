#include "ToolManager.h"
#include "../RenderTarget/RenderTarget.h"

void ToolManager::paintOnPress(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::MouseContext mouse)
{
    if (tool != nullptr)
        tool->paintOnPress(data, tmp, mouse, color);
}

void ToolManager::paintOnMove(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::MouseContext mouse)
{   
    if (tool != nullptr)
        tool->paintOnMove(data, tmp, mouse, color);
}

void ToolManager::paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::MouseContext mouse)
{
    if (tool != nullptr)
        tool->paintOnRelease(data, tmp, mouse, color);
}

void ToolManager::disableTool(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::MouseContext mouse)
{
    if (tool != nullptr)
        tool->disable(data, tmp, mouse, color);
}

void ToolManager::setTool(plugin::ToolI* new_tool)
{
    tool = new_tool;
}

void ToolManager::setColor(plugin::Color new_color)
{
    color = new_color;
}
