#ifndef SYM_FILTER_MANAGER
#define SYM_FILTER_MANAGER

#include "../Filter/Filter.h"
#include "../RenderTarget/RenderTarget.h"
#include "../Standart/FilterI.h"

class FilterManager : public plugin::FilterManagerI
{
    Filter       *last_filter;
    RenderTarget *rt;
    bool          active;

public:
    FilterManager(RenderTarget* _rt          = nullptr, 
                  Filter*       _last_filter = nullptr)
    {
        last_filter = _last_filter;
        rt          = _rt;
        active      = false;
    }

    void    setFilter      (plugin::FilterI* filter)   override;
    void    setRenderTarget(plugin::RenderTargetI* rt) override;
    void    applyFilter    ()                          override;
    Filter* GetFilter      ();
    bool    GetActive      ();
};

#endif //SYM_FILTER_MANAGER