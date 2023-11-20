#include "VerticalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void VerticalMenu::registerSubWidget(Widget* new_widget)
{
    Widget* last_w = sub_widgets.data[sub_widgets.End()].val;
    
    plugin::Vec2 new_pos = last_w->GetPosition() + plugin::Vec2(0, last_w->GetSize().GetY());
    new_widget->Move(new_pos - new_widget->GetPosition());

    Menu::registerSubWidget(new_widget);
}

