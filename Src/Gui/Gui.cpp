#include "Gui.h"
#include "../ClipRegion/ClipRegion.h"
#include "../RegionSet/RegionSet.h"

plugin::RenderTargetI* Gui::getRenderTarget(plugin::Vec2    size, 
                                            plugin::Vec2    pos, 
                                            plugin::Plugin *self)
{
    rt_widget = new RectangleWidget(pos, size);
    root->registerSubWidget(rt_widget);

    return (plugin::RenderTargetI*)rt_widget->GetRT();
}

void Gui::createParamWindow(plugin::Array<const char*> param_names, 
                            plugin::Interface*         self)
{
    //...
}

