#ifndef SYM_FILTER
#define SYM_FILTER

#include "../RenderTarget/RenderTarget.h"
#include "../DynArray.h"
#include "../Standart/Standart.h"

class Filter : public plugin::FilterI
{

protected:
    plugin::Array<const char*> param_names;

public :
    Filter() :
    param_names(0, nullptr)
    {}

    virtual plugin::Array<const char*> getParamNames() const override 
    { return plugin::Array<const char*>(0, nullptr); }
    virtual plugin::Array<double>  getParams() const override 
    { return plugin::Array<double>(0, nullptr); }
    
    virtual void apply    (plugin::RenderTargetI *data)  override {}
    virtual void setParams(plugin::Array<double> params) override {}
};

#endif //SYM_FILTER