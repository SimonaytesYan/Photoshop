#ifndef SYM_TOOL_MANAGER
#define SYM_TOOL_MANAGER

#include "../Tool/Tool.h"
#include "../Color.h"
#include "../Keys.h"
#include "../Standart/Standart.h"

class RenderTarget;

class ToolManager : plugin::ToolManagerI
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
                        plugin::MouseContext mouse) override;
    void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse) override;
    void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse) override;
    void disableTool   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse) override;

    void setTool (plugin::ToolI* new_tool) override;
    void setColor(plugin::Color new_color) override;

    plugin::ToolI* getTool () override
    { return tool; }
    plugin::Color  getColor() override
    { return color; }
};

#endif //SYM_TOOL_MANAGER