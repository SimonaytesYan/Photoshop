#ifndef SYM_PLUGIN_BRUSH
#define SYM_PLUGIN_BRUSH

#include "../../Src/Standart/Standart.h"
#include "../../Src/List.h"

extern "C" plugin::Plugin* getInstance(plugin::App *app);

class BrushTool;

class BrushPlugin : public plugin::Plugin
{
    plugin::App* app;
    BrushTool*   tool;

public:
    BrushPlugin(plugin::App* app);

    plugin::Interface *getInterface() override
    { return (plugin::Interface*) tool; }
    
    ~BrushPlugin()
    {}
};

class BrushTool : public plugin::ToolI
{
    plugin::Array<const char*> param_names;
    double                     thickness;
    bool                       drawing;
    List<plugin::Vec2>         vertexes;

public:
    BrushTool(double _thickness) :
    thickness(_thickness),
    drawing  (false),
    vertexes (List<plugin::Vec2>(0))
    {}

    virtual void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override;
    virtual void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override;
    virtual void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override;
    virtual void disable       (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override;
    
    const plugin::Texture* getIcon() override 
    { return nullptr; }

    void                       setParams    (plugin::Array<double> params) override;
    plugin::Array<const char*> getParamNames()                             override;
    plugin::Array<double>      getParams    ()                             override;

    ~BrushTool()
    {}
};


#endif // SYM_PLUGIN_BRUSH