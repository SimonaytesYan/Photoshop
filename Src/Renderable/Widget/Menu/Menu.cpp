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
        expanded = false;
    }
    else
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
    {
        size = new_widget->GetPosition() + new_widget->GetSize() - position;
    }
    else
    {
        expanded_size = new_widget->GetPosition() + new_widget->GetSize();
    }

    Widget::AddObject(new_widget);
}

void Menu::Render(RenderTarget* render_target)
{
    static bool first_enter_after_change_view = true;
    if (!static_menu)
    {

        if (first_enter_after_change_view)
        {
            first_enter_after_change_view = false;

            if (expanded)
                size = expanded_size;
            else
                size = collapsed_size;
            
            UpdateRegionSet();
        }
    }

    Widget::Render(render_target);
}

