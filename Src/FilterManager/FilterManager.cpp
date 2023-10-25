#include "FilterManager.h"


Filter* FilterManager::GetFilter()
{
    return last_filter;
}

bool FilterManager::GetActive()
{
    return active;
}

void FilterManager::SetFilter(Filter* filter)
{
    last_filter = filter;
    active      = true;
}

void FilterManager::SetRenderTarget(RenderTarget* _rt)
{
    rt = _rt;
}

void FilterManager::ApplyLastFilter()
{
    if (active)
    {
        last_filter->Apply(*rt);
        active = false;
    }
}
