#include "Menu.h"
#include "../../../ClipRegion/ClipRegion.h"

Menu::Menu(Button* button, bool _static_menu) :
Widget        (button->GetPosition(), button->GetSize()),
expanded_size (button->GetSize()),
collapsed_size(button->GetSize()),
main_button   (button),
static_menu   (_static_menu)
{
    if (!_static_menu)
    {
        button->ChangePressFunction(CallChangeExpandedStatus, this);
        button->SetAvailable(true);
        expanded = false;
    }
    Widget::AddObject(button);
}

Menu::Menu(Widget* widget) :
Widget        (widget->GetPosition(), widget->GetSize()),
expanded_size (widget->GetSize()),
collapsed_size(widget->GetSize()),
main_button   (widget),
static_menu   (true)
{
    Widget::AddObject(widget);
    expanded = true;
}

void Menu::ChangeExpandedStatus()
{
    expanded = !expanded;

    if (!static_menu)
    {
        if (expanded)
        {
            for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
                sub_widgets[i].val->SetAvailable(true);
            UpdateDefaultRegionSet();

            UpdateRegionSet();             
        }
        else
        {
            UpdateRegionSet();
            for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
                sub_widgets[i].val->SetAvailable(false);
                
            main_button->SetAvailable(true);
        }

        UpdateRegionSet();
    }
}

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
        default_reg_set.ChangeElem(0, ClipRegion(position, size));
        Widget::AddObject(new_widget);
    }
    else
    {
        expanded_size = new_widget->GetPosition() + new_widget->GetSize() - position;
        Widget::AddObject(new_widget);
        new_widget->SetAvailable(false);
    }

    UpdateRegionSet();
}

void Menu::Render(RenderTarget* rt)
{
    Widget::Render(rt);
}

void Menu::UpdateDefaultRegionSet()
{
    default_reg_set.Clear();

    if (expanded)
        for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
        {
            if (sub_widgets[i].val->GetAvailable())
                default_reg_set += sub_widgets[i].val->GetDefaultRegSet();
        }
    else
        default_reg_set.AddRegion(ClipRegion(position, collapsed_size));
}

bool Menu::OnMouseMove(MouseCondition mouse)
{
    if (!InsideP(mouse.position))
        if (expanded)
            ChangeExpandedStatus();

    return Widget::OnMouseMove(mouse);
}

bool Menu::InsideP(Vector v)
{
    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
    {
        if (sub_widgets[i].val->GetAvailable() && sub_widgets[i].val->InsideP(v))
            return true;
    }

    return false;
}
