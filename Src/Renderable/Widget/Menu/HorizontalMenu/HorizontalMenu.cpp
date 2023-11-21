#include "HorizontalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void HorizontalMenu::registerSubWidget(plugin::WidgetI* new_widget)
{
    WidgetPtr last_w = sub_widgets.data[sub_widgets.End()].val;
    
    plugin::Vec2 new_pos = last_w.getPos() + plugin::Vec2(last_w.getSize().GetX(), 0);
    new_widget->move(new_pos - new_widget->getPos());

    Menu::registerSubWidget(new_widget);
}

