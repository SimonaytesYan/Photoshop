#ifndef SYM_TOOL_MANAGER
#define SYM_TOOL_MANAGER

#include "../Tool/Tool.h"
#include "../Color.h"
#include "../Keys.h"

class RenderTarget;

class ToolManager
{
    Tool* tool;
    plugin::Color color;

public :
    ToolManager()
    {
        tool  = nullptr;
        color = plugin::Color(255, 255, 255);
    }
    
    void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, MouseContext mouse);
    void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, MouseContext mouse);
    void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, MouseContext mouse);
    void DisableTool   (RenderTarget& data, RenderTarget& tmp, MouseContext mouse);

    void ChangeTool    (Tool* new_tool);
    void ChangeColor   (plugin::Color new_color);
};

#endif //SYM_TOOL_MANAGER