#ifndef SYM_TOOL_MANAGER
#define SYM_TOOL_MANAGER

#include "../Tool/Tool.h"
#include "../Color.h"
#include "../Keys.h"
#include "../Standart/ToolI.h"

class RenderTarget;

class ToolManager : plugin::ToolManagerI
{
    Tool* tool;
    plugin::Color color;

public :
    ToolManager()
    {
        tool  = nullptr;
        color = plugin::Color(255, 255, 255);
    }
    
    void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse) override;
    void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse) override;
    void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse) override;
    void disableTool   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse) override;

    void ChangeTool    (Tool* new_tool);
    void ChangeColor   (plugin::Color new_color);
};

#endif //SYM_TOOL_MANAGER