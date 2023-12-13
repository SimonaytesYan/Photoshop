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
Widget        (button->getPos(), button->getSize()),
main_button   (button),
static_menu   (_static_menu)
{
    if (!_static_menu)
    {
        button->ChangePressFunction(new CallChangeExpandedStatus(this));
        button->setAvailable(true);
        button->setVisible(true);
        expanded = false;
    }
    else
        expanded = true;

    Widget::registerSubWidget(button);
}

Menu::Menu(Widget* widget) :
Widget        (widget->getPos(), widget->getSize()),
main_button   (widget),
static_menu   (true)
{
    Widget::registerSubWidget(widget);
    expanded = true;

    fprintf(stderr, "Static menu\n");
}

void Menu::ChangeExpandedStatus()
{
    expanded = !expanded;

    if (!static_menu)
    {
        if (expanded)
        {
            for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
                sub_widgets[i].val->setVisible(true);
        }
        else
        {
            for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
                sub_widgets[i].val->setVisible(false);            
            main_button->setVisible(true);
        }
        UpdateDefaultRegionSet();
        UpdateRegionSet();
    }
}

void Menu::registerSubWidget(plugin::WidgetI* new_widget)
{
    if (static_menu)
    {
        Widget::registerSubWidget(new_widget);
        UpdateOwnDefaultRegionSet();
    }
    else
    {
        Widget::registerSubWidget(new_widget);
        ((Widget*)new_widget)->setVisible(false);
    }

    UpdateRegionSet();
}

void Menu::UpdateOwnDefaultRegionSet()
{
    default_reg_set.Clear();

    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
    {
        if (sub_widgets[i].val->getAvailable() && sub_widgets[i].val->getVisible())
            default_reg_set += sub_widgets[i].val->GetDefaultRegSet();
    }
}

bool Menu::onMouseMove(plugin::MouseContext mouse)
{
    if (!InsideP(mouse.position))
    {
        if (expanded && !static_menu)
        {
            ChangeExpandedStatus();
        }
    }

    if (expanded)
        return Widget::onMouseMove(mouse);

    return main_button->onMouseMove(mouse);
}

bool Menu::onMouseRelease(plugin::MouseContext mouse)
{
    if (expanded)
        return Widget::onMouseRelease(mouse);
    
    return main_button->onMouseRelease(mouse);
}

bool Menu::onMousePress(plugin::MouseContext mouse)
{
    if (expanded)
        return Widget::onMousePress(mouse);
    
    return main_button->onMousePress(mouse);
}

bool Menu::onKeyboardPress(plugin::KeyboardContext keyboard)
{
    if (expanded)
        return Widget::onKeyboardPress(keyboard);
    
    return main_button->onKeyboardPress(keyboard);
}

bool Menu::onKeyboardRelease(plugin::KeyboardContext keyboard)
{
    if (expanded)
        return Widget::onKeyboardRelease(keyboard);
    
    return main_button->onKeyboardRelease(keyboard);
}

bool Menu::onClock(size_t delta)
{
    if (expanded)
        return Widget::onClock(delta);
    
    return main_button->onClock(delta);
}

bool Menu::InsideP(plugin::Vec2 v)
{
    static int k = 0;

    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
    {
        if (sub_widgets[i].val->getAvailable() && sub_widgets[i].val->getVisible() && 
            sub_widgets[i].val->InsideP(v))
        {
            return true;
        }
    }

    return false;
}