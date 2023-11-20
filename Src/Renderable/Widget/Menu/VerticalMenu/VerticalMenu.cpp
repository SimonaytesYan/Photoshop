#include "VerticalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void VerticalMenu::registerSubWidget(Widget* new_widget)
{
    Widget* last_w = sub_widgets.data[sub_widgets.End()].val;
    
    plugin::Vec2 new_pos = last_w->getPosition() + plugin::Vec2(0, last_w->getSize().GetY());
    new_widget->move(new_pos - new_widget->getPosition());

    Menu::registerSubWidget(new_widget);
}

