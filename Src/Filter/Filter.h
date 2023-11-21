#ifndef SYM_FILTER
#define SYM_FILTER

#include "../RenderTarget/RenderTarget.h"
#include "../DynArray.h"
#include "../Standart/FilterI.h"

class Filter : public plugin::FilterI
{
public :

    virtual plugin::Array<const char*> getParamNames() override 
    { return plugin::Array<const char*>(0, nullptr); }
    virtual plugin::Array<double>      getParams()     override 
    { return plugin::Array<double>(0, nullptr); }
    
    virtual void apply    (plugin::RenderTargetI *data)  override {}
    virtual void setParams(plugin::Array<double> params) override {}
};

#endif //SYM_FILTER