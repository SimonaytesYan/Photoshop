#include "RectangleWidget.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"
#include <typeinfo>

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

    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
    {
        fprintf(stderr, "sub_widget[%d] = %s(%p)\n", i, typeid(*sub_widgets[i].val).name(), sub_widgets[i].val);
    }
    fprintf(stderr, "\n");

    Widget::render(render_target);
}