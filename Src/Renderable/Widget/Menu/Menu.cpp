#include "Menu.h"
#include "../../../ClipRegion/ClipRegion.h"

Menu::Menu(Button* button, bool _static_menu) :
           Widget(button->GetPosition(), button->GetSize()),
expanded_size (button->GetSize()),
collapsed_size(button->GetSize()),
static_menu   (_static_menu)
{
    if (!_static_menu)
    {
        button->ChangePressFunction(CallChangeExpandedStatus, this);
        button->SetAvailable(true);
        expanded = false;
    }
    Widget::AddObject(button);
};

void CallChangeExpandedStatus(void* _args)
{
    Menu* args = (Menu*)_args;
    args->ChangeExpandedStatus();
}

void Menu::AddObject(Widget* new_widget)
{
    if (static_menu)
        size = new_widget->GetPosition() + new_widget->GetSize() - position;
    else
    {
        expanded_size = new_widget->GetPosition() + new_widget->GetSize() - position;
    }

    Widget::AddObject(new_widget);
    
    new_widget->SetAvailable(false);
    UpdateRegionSet();
}

void Menu::Render(RenderTarget* rt)
{
    Widget::Render(rt);
}
