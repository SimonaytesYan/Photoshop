#include "VerticalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void VerticalMenu::AddObject(Widget* new_widget)
{
    Widget* last_w = sub_widgets.data[sub_widgets.End()].val;
    
    Vector new_pos = last_w->GetPosition() + Vector(0, last_w->GetSize().GetY());
    new_widget->Move(new_widget->GetPosition() - new_pos);

    Menu::AddObject(new_widget);
}

