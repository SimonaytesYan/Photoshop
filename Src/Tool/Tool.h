#ifndef SYM_TOOL
#define SYM_TOOL

#include "../Vec2/Vec2.h"
#include "../Color.h"
#include "../Keys.h"
#include "../Standart/ToolI.h"

class RenderTarget;

class Tool : public plugin::ToolI
{
    
protected :

    plugin::Texture icon;
    plugin::Vec2    start_pos;
    plugin::Vec2    last_pos;
    bool            drawing;

public :
    Tool() :
    start_pos (plugin::Vec2(-1, -1)),
    last_pos  (plugin::Vec2(-1, -1)),
    drawing   (false),
    icon      (plugin::Texture())
    {};

    Tool(plugin::Texture new_icon) :
    start_pos (plugin::Vec2(-1, -1)),
    last_pos  (plugin::Vec2(-1, -1)),
    drawing   (false),
    icon      (plugin::Texture(icon))
    {};

    
    void setColor(plugin::Color color) = 0;
    void setTool (ToolI *tool)         = 0;

    virtual void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color) override
                                {}
    virtual void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color) override
                                {}
    virtual void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color) override
                                {}
    virtual void disable       (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color) override
                                {}
};

#endif //SYM_TOOL