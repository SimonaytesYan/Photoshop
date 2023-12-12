#include "VerticalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void VerticalMenu::registerSubWidget(plugin::WidgetI* new_widget)
{
    Widget* last_w = sub_widgets.data[sub_widgets.End()].val;
    
    plugin::Vec2 new_pos = last_w.getPos() + plugin::Vec2(0, last_w.getSize().GetY());
    new_widget->move(new_pos - new_widget->getPos());

    Menu::registerSubWidget(new_widget);
}

