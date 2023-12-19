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

    #ifdef DEBUG
        fprintf(stderr, "vis = %d avl = %d\n", visible, available);
    
        for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
        {
            fprintf(stderr, "sub_widget[%d] = %s(%p) vis = %d avl = %d\n", i, typeid(*sub_widgets[i].val).name(), 
                                                                  sub_widgets[i].val, sub_widgets[i].val->getVisible(),
                                                                  sub_widgets[i].val->getAvailable());
        }
        fprintf(stderr, "\n");
    #endif

    Widget::render(render_target);
}