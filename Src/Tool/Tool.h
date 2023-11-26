#ifndef SYM_TOOL
#define SYM_TOOL

#include "../Standart/Standart.h"

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

    virtual void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override
                                {}
    virtual void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override
                                {}
    virtual void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override
                                {}
    virtual void disable       (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override
                                {}
    
    const plugin::Texture*           getIcon()       override { return &icon; }
          plugin::Array<const char*> getParamNames() override { return plugin::Array<const char*>(0, nullptr); }
          plugin::Array<double>      getParams()     override { return plugin::Array<double>(0, nullptr); }
    
    void setParams(plugin::Array<double> params) override {}
};

#endif //SYM_TOOL