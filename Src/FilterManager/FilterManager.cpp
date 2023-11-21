#include "FilterManager.h"


Filter* FilterManager::GetFilter()
{
    return last_filter;
}

bool FilterManager::GetActive()
{
    return active;
}

void FilterManager::setFilter(Filter* filter)
{
    last_filter = filter;
    active      = true;
}

void FilterManager::setRenderTarget(RenderTarget* _rt)
{
    rt = _rt;
}

void FilterManager::applyFilter()
{
    if (active && last_filter != nullptr)
    {
        last_filter->apply(*rt);
        active = false;
    }
}
