#include "HorizontalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void HorizontalMenu::registerSubWidget(plugin::WidgetI* new_widget)
{
    plugin::Vec2 new_pos = plugin::Vec2(0, 0);
    if (sub_widgets.End() != -1)
    {
        Widget* last_w = sub_widgets[sub_widgets.End()].val;
        new_pos = last_w->getPos() + plugin::Vec2(last_w->getSize().x, 0);
    }
    else
        new_pos = position;

    new_widget->move(new_pos - new_widget->getPos());

    Menu::registerSubWidget(new_widget);
}

