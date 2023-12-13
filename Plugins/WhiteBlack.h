#include "../Src/Standart/Standart.h"

//#include "Plugin.h"

extern "C" plugin::Plugin* getInstance(plugin::App *app);

class WhiteAndBlackFilter;

class SymWhiteAndBlackPlugin : public plugin::Plugin
{
    plugin::App*         app;
    WhiteAndBlackFilter* filter;


public:
    SymWhiteAndBlackPlugin(plugin::App* app);

    plugin::Interface *getInterface() const override
    { return (plugin::Interface*) filter; }
    
    void selectPlugin() override
    {}

    ~SymWhiteAndBlackPlugin()
    {}
};

class WhiteAndBlackFilter : public plugin::FilterI
{
    plugin::Array<const char*> param_names;

public:
    void                       apply        (plugin::RenderTargetI* rt)    override;
    void                       setParams    (plugin::Array<double> params) override;
    plugin::Array<const char*> getParamNames() const                       override;
    plugin::Array<double>      getParams    () const                       override;

    WhiteAndBlackFilter() :
    param_names (plugin::Array<const char*>(0, nullptr))
    {}

    ~WhiteAndBlackFilter()
    {}
};

