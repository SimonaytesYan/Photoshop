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

    plugin::Interface *getInterface() const override
    { return (plugin::Interface*) tool; }
    
    void selectPlugin() override
    {}

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
    thickness   (_thickness),
    drawing     (false),
    vertexes    (List<plugin::Vec2>(0)),
    param_names (plugin::Array<const char*>(0, nullptr))
    {}

    virtual void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override;
    virtual void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override;
    virtual void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override;
    virtual void disable       (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                plugin::MouseContext mouse, plugin::Color color) override;
    
    const plugin::Texture* getIcon() const override 
    { return nullptr; }

    void                       setParams    (plugin::Array<double> params) override;
    plugin::Array<const char*> getParamNames() const                       override;
    plugin::Array<double>      getParams    () const                       override;

    ~BrushTool()
    {}
};


#endif // SYM_PLUGIN_BRUSH