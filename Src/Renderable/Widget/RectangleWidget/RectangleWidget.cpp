#include "RectangleWidget.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

RectangleWidget::RectangleWidget(plugin::Vec2 position,    plugin::Vec2 size,
                                 plugin::Color background, bool         available) :
Widget (position, size, available),
rt     (RenderTarget(size))
{
    rt.clear(background);
}

RectangleWidget::RectangleWidget(plugin::Vec2 position, plugin::Vec2 size, 
                                 bool         available) :
Widget (position, size, available),
rt     (RenderTarget(size))
{
    rt.clear();
}

void RectangleWidget::render(RenderTarget* render_target)
{
    render_target->DrawSprite(position, rt.GetTexture(), reg_set);
    Widget::render(render_target);
}