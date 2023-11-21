#include "FilterManager.h"


plugin::FilterI* FilterManager::GetFilter()
{
    return last_filter;
}

bool FilterManager::GetActive()
{
    return active;
}

void FilterManager::setFilter(plugin::FilterI* filter)
{
    last_filter = filter;
    active      = true;
}

void FilterManager::setRenderTarget(plugin::RenderTargetI* _rt)
{
    rt = _rt;
}

void FilterManager::applyFilter()
{
    if (active && last_filter != nullptr)
    {
        last_filter->apply(rt);
        active = false;
    }
}
