#include "Menu.h"
#include "../../../ClipRegion/ClipRegion.h"

struct CallChangeExpandedStatus : public ButtonFunction
{
    Menu* menu;

    CallChangeExpandedStatus(Menu* _menu) :
    menu(_menu)
    {}

    void operator()() override
    {
        menu->ChangeExpandedStatus();
    }
};

Menu::Menu(Button* button, bool _static_menu) :
Widget        (button->GetPosition(), button->GetSize()),
main_button   (button),
static_menu   (_static_menu)
{
    if (!_static_menu)
    {
        button->ChangePressFunction(new CallChangeExpandedStatus(this));
        button->setAvailable(true);
        expanded = false;
    }
    Widget::registerSubWidget(button);
}

Menu::Menu(Widget* widget) :
Widget        (widget->GetPosition(), widget->GetSize()),
main_button   (widget),
static_menu   (true)
{
    Widget::registerSubWidget(widget);
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
                sub_widgets[i].val->setAvailable(true);
        }
        else
        {
            for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
                sub_widgets[i].val->setAvailable(false);            
            main_button->setAvailable(true);
        }
        UpdateDefaultRegionSet();
        UpdateRegionSet();
    }
}

void Menu::registerSubWidget(Widget* new_widget)
{
    if (static_menu)
    {
        Widget::registerSubWidget(new_widget);
        UpdateOwnDefaultRegionSet();
    }
    else
    {
        Widget::registerSubWidget(new_widget);
        new_widget->setAvailable(false);
    }

    UpdateRegionSet();
}

void Menu::UpdateOwnDefaultRegionSet()
{
    default_reg_set.Clear();

    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
    {
        if (sub_widgets[i].val->getAvailable())
            default_reg_set += sub_widgets[i].val->GetDefaultRegSet();
    }
}

bool Menu::onMouseMove(MouseContext mouse)
{
    if (!InsideP(mouse.position))
    {
        if (expanded)
            ChangeExpandedStatus();
    }

    return Widget::onMouseMove(mouse);
}

bool Menu::InsideP(plugin::Vec2 v)
{
    static int k = 0;

    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
    {
        if (sub_widgets[i].val->getAvailable() && sub_widgets[i].val->InsideP(v))
        {
            return true;
        }
    }

    return false;
}
