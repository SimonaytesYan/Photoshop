#ifndef SYM_TOOL_MANAGER
#define SYM_TOOL_MANAGER

#include "../Tool/Tool.h"
#include "../Standart/Standart.h"

class RenderTarget;

class ToolManager
{
    plugin::ToolI* tool;
    plugin::Color color;

public :
    ToolManager()
    {
        tool  = nullptr;
        color = plugin::Color(255, 255, 255);
    }
    
    void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse);
    void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse);
    void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse);
    void disableTool   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse);

    void setTool (plugin::ToolI* new_tool);
    void setColor(plugin::Color new_color);

    plugin::ToolI* getTool ()
    { return tool; }
    plugin::Color  getColor()
    { return color; }
};

#endif //SYM_TOOL_MANAGER