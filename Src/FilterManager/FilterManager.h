#ifndef SYM_FILTER_MANAGER
#define SYM_FILTER_MANAGER

#include "../Filter/Filter.h"
#include "../RenderTarget/RenderTarget.h"
#include "../Standart/Standart.h"

class FilterManager : public plugin::FilterManagerI
{
    plugin::FilterI       *last_filter;
    plugin::RenderTargetI *rt;
    bool                   active;

public:
    FilterManager(plugin::RenderTargetI* _rt          = nullptr, 
                  plugin::FilterI*       _last_filter = nullptr)
    {
        last_filter = _last_filter;
        rt          = _rt;
        active      = false;
    }

    void    setFilter      (plugin::FilterI* filter)   override;
    void    setRenderTarget(plugin::RenderTargetI* rt) override;
    void    applyFilter    ()                          override;
    
    plugin::FilterI* GetFilter();
    bool             GetActive();
};

#endif //SYM_FILTER_MANAGER