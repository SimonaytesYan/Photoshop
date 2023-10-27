#include "Menu.h"
#include "../../../ClipRegion/ClipRegion.h"

Menu::Menu(Button* button, bool _static_menu) :
           Widget(button->GetPosition(), button->GetSize()),
           expanded_objects (List<Widget*>(0)),
           collapsed_objects(List<Widget*>(0))
{
    static_menu = _static_menu;
    if (!_static_menu)
    {
        button->ChangePressFunction(CallChangeExpandedStatus, this);

        collapsed_objects.PushBack(button);
        expanded_objects.PushBack(button);
        
        expanded = false;
    }
    else if (button != nullptr)
        AddObject(button);
};

void CallChangeExpandedStatus(void* _args)
{
    Menu* args = (Menu*)_args;
    args->ChangeExpandedStatus();
}

void Menu::AddObject(Widget* new_widget)
{
    if (!static_menu)
        expanded_objects.PushBack(new_widget);
    else
        Widget::AddObject(new_widget);
}

void Menu::Render(RenderTarget* render_target)
{
    if (!static_menu)
    {
        static bool first_enter_after_change_view = true;

        if (first_enter_after_change_view)
        {
            first_enter_after_change_view = false;

            if (expanded)
                sub_widgets = expanded_objects;
            else
                sub_widgets = collapsed_objects;
            
            UpdateRegionSet();
        }
    }

    Widget::Render(render_target);
}

