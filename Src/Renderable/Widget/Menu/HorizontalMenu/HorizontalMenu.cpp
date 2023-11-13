#include "HorizontalMenu.h"
#include "../../../../ClipRegion/ClipRegion.h"

void HorizontalMenu::AddObject(Widget* new_widget)
{
    Widget* last_w = sub_widgets.data[sub_widgets.End()].val;
    
    Vec2 new_pos = last_w->GetPosition() + Vec2(last_w->GetSize().GetX(), 0);
    new_widget->Move(new_pos - new_widget->GetPosition());

    Menu::AddObject(new_widget);
}

