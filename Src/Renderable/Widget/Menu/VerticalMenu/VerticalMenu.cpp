#include "VerticalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void VerticalMenu::registerSubWidget(plugin::WidgetI* new_widget)
{
    plugin::Vec2 new_pos = plugin::Vec2(0, 0);
    if (sub_widgets.size != 0)
    {
        Widget* last_w = sub_widgets[sub_widgets.End()].val;
        new_pos = last_w->getPos() + plugin::Vec2(0, last_w->getSize().GetY());
    }
    else
        new_pos = position;

    new_widget->move(new_pos - new_widget->getPos());

    Menu::registerSubWidget(new_widget);
}

