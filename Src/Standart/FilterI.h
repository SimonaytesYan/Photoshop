#ifndef SYM_FILTER_I
#define SYM_FILTER_I

#include "Interface.h"
#include "RenderTargetI.h"

namespace plugin
{
    struct FilterI: public Interface 
    {
        virtual void apply(RenderTargetI *data) = 0;
    };

    struct FilterManagerI 
    {
        virtual void setRenderTarget(RenderTargetI *target) = 0;
        virtual void setFilter(FilterI *filter) = 0;
        virtual void applyFilter() = 0;
    };
}

#endif //SYM_FILTER_I