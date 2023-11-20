#include "HorizontalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void HorizontalMenu::registerSubWidget(Widget* new_widget)
{
    Widget* last_w = sub_widgets.data[sub_widgets.End()].val;
    
    plugin::Vec2 new_pos = last_w->getPosition() + plugin::Vec2(last_w->getSize().GetX(), 0);
    new_widget->move(new_pos - new_widget->getPosition());

    Menu::registerSubWidget(new_widget);
}

