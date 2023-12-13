#include "Widget.h"
#include "../Renderable.h"
#include "../../Standart/Standart.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../Useful.h"

const double kPrecision = 1e-6;

Widget::Widget (plugin::Vec2 _position, plugin::Vec2 _size, bool _available) :
Renderable      (),
available       (_available),
visible         (true),
position        (_position),
size            (_size),
sub_widgets     (List<Widget*>(0)),
reg_set         (RegionSet()),
default_reg_set (RegionSet()),
parent          (nullptr)
{
    UpdateDefaultRegionSet();
    reg_set.AddRegion(ClipRegion(_position, _size));
}

Widget::~Widget()
{
}

void Widget::move(plugin::Vec2 delta)
{
    position = position + delta;
    for (int i = 0; i < default_reg_set.GetLength(); i++)
    {
        ClipRegion reg(delta + default_reg_set[i].getPos(), 
                       default_reg_set[i].getSize());
        default_reg_set.ChangeElem(i, reg);
    }

    for (int i = 0; i < reg_set.GetLength(); i++)
    {
        reg_set.ChangeElem(i, ClipRegion(delta + reg_set[i].getPos(), 
                                         reg_set[i].getSize()));
    }

    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
        sub_widgets[i].val->move(delta);
}

void Widget::unregisterSubWidget(WidgetI* son)
{
    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
    {
        if (sub_widgets[index].val == son)
        {
            sub_widgets.Remove(index);
            break;
        }
    }
}

void Widget::render(plugin::RenderTargetI* render_target)
{
    if (available && visible)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
        {
            Widget* sub_widget = sub_widgets[index].val;
            if (sub_widget->getAvailable() && sub_widget->getVisible())
            {
                sub_widget->render(render_target);
            }
        }
    }
}

void Widget::render(RenderTarget* render_target)
{
    if (available && visible)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
        {
            Widget* sub_widget = sub_widgets[index].val;
            if (sub_widget->getAvailable() && sub_widget->getVisible())
            {
                sub_widget->render(render_target);
            }
            else
            {
                unregisterSubWidget(sub_widget);
                UpdateRegionSet();
            }
        }
    }
}

void Widget::registerSubWidget(WidgetI* new_widget)
{
    new_widget->setParent(this);
    sub_widgets.PushBack((Widget*)new_widget);

    UpdateRegionSet();
}

bool WidgetEventRound(Events event, void*  event_args, 
                      List<Widget*> &objects, bool available, bool visible)
{
    if (!available || !visible)
        return false;

    bool intercepted = false;
    int index        = objects.End();
    while (index != -1)
    {
        switch (event)
        {
        case KEY_PRESS:
            intercepted = objects[index].val->onKeyboardPress(*(plugin::KeyboardContext*)event_args);
            break;
        case KEY_RELEASE:
            intercepted = objects[index].val->onKeyboardRelease(*(plugin::KeyboardContext*)event_args);
            break;
        case MOUSE_PRESS:
            intercepted = objects[index].val->onMousePress(*(plugin::MouseContext*)event_args);
            break;
        case MOUSE_RELEASE:
            intercepted = objects[index].val->onMouseRelease(*(plugin::MouseContext*)event_args);
            break;
        case MOUSE_MOVE:
            intercepted = objects[index].val->onMouseMove(*(plugin::MouseContext*)event_args);
            break;
        case ON_CLOCK:
            intercepted = objects[index].val->onClock(*(size_t*)event_args);
            break;
        
        default:
            break;
        }
        if (intercepted)
            break;
        index = objects.Deterate(index);
    }

    return intercepted;
}

bool Widget::onKeyboardPress(plugin::KeyboardContext key)
{
    return WidgetEventRound(KEY_PRESS, &key, sub_widgets, available, visible);
}

bool Widget::onKeyboardRelease(plugin::KeyboardContext key)
{
    return WidgetEventRound(KEY_RELEASE, &key, sub_widgets, available, visible);
}

void Widget::ToForeground(Widget* son)
{
    int index = 0;
    for (index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
    {
        if (son == sub_widgets[index].val)
            break;
    }

    // Check if son didn`t found
    if (index == -1)
        return;

    // Put son to foreground
    if (sub_widgets.End() != index)
    {   
        sub_widgets.Remove(index);
        sub_widgets.PushBack(son);

        UpdateRegionSet();
    }
}

bool Widget::onMousePress(plugin::MouseContext mouse)
{
    fprintf(stderr, "On mouse (%lg, %lg) widget press %p\n", mouse.position.x, mouse.position.y, this);

    fprintf(stderr, "pos  = (%lg, %lg)\n",   position.x, position.y);
    fprintf(stderr, "size = (%lg, %lg)\n\n", size.x, size.y);

    if (InsideP(mouse.position))
    {
        if (parent != nullptr)
            parent->ToForeground(this);
        return WidgetEventRound(MOUSE_PRESS, &mouse, sub_widgets, available, visible);
    }
    return false;
}
 
bool Widget::onMouseRelease(plugin::MouseContext mouse)
{
    return WidgetEventRound(MOUSE_RELEASE, &mouse, sub_widgets, available, visible);
}

bool Widget::onMouseMove(plugin::MouseContext mouse)
{
    return WidgetEventRound(MOUSE_MOVE, &mouse, sub_widgets, available, visible);
}

bool Widget::onClock(size_t delta)
{
    return WidgetEventRound(ON_CLOCK, &delta, sub_widgets, available, visible);
}

void Widget::UpdateRegionSet()
{
    int cnt = 0;
    Widget* root = this;
    while (root->parent != nullptr)
    {
        root = root->parent;
    }

    root->recalcRegion();
}

void Widget::recalcRegion()
{
    if (!available || !visible)
        return;
    
    reg_set = default_reg_set;  // Set region set to default region set

    if (parent != nullptr)                              
    {
        reg_set &= parent->reg_set;                 // Intersect with parent

        // Remove upper brothers from this

        // Skip lower brothers 
        int index = 0;
        for (index = parent->sub_widgets.Begin(); index != -1; index = parent->sub_widgets.Iterate(index))
        {
            if (parent->sub_widgets[index].val == this)
                break;
        }
        
        index = parent->sub_widgets.Iterate(index);     // Skip itself
        
        // Intersect with brothers
        for (index; index != -1; index = parent->sub_widgets.Iterate(index))
        {
            Widget* brother = parent->sub_widgets[index].val;
            reg_set -= brother->GetDefaultRegSet();
        }
    }

    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))  // Update children
    {
        Widget* sub_w = sub_widgets[index].val;
        
        if (sub_w->getAvailable() && sub_w->getVisible())
            sub_w->recalcRegion();
    }

    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index)) // Remove children from this
    {
        Widget* sub_w = sub_widgets[index].val;
        if (sub_w->getAvailable() && sub_w->getVisible())
            reg_set -= sub_w->GetDefaultRegSet();
    }
}

void Widget::UpdateParentDefaultRegionSet()
{
    Widget* current = this;
    while (current != nullptr)
    {
        current->UpdateOwnDefaultRegionSet();
        current = current->parent;
    }
}

void Widget::UpdateOwnDefaultRegionSet()
{
    default_reg_set.Clear();
    default_reg_set.AddRegion(ClipRegion(position, size));
}

void Widget::UpdateDefaultRegionSet()
{
    UpdateOwnDefaultRegionSet();
    UpdateParentDefaultRegionSet();
}

bool Widget::InsideP(plugin::Vec2 v)
{
    return v.GetX() - position.GetX() >= -kPrecision &&
           v.GetX() - position.GetX() <= size.GetX() + kPrecision &&
           v.GetY() - position.GetY() >= -kPrecision && 
           v.GetY() - position.GetY() <= size.GetY() + kPrecision;
}

//========================PLUGIN WIDGET=========================================

void PluginWidget::render(plugin::RenderTargetI* render_target)
{
    plugin_widget_i->render(render_target);
}

bool PluginWidget::onKeyboardPress(plugin::KeyboardContext key)
{
    return plugin_widget_i->onKeyboardPress(key);
}

bool PluginWidget::onKeyboardRelease(plugin::KeyboardContext key)
{
    return plugin_widget_i->onKeyboardRelease(key);
}

bool PluginWidget::onMousePress(plugin::MouseContext mouse)
{
    return plugin_widget_i->onMousePress(mouse);
}

bool PluginWidget::onMouseRelease(plugin::MouseContext mouse)
{
    return plugin_widget_i->onMouseRelease(mouse);
}

bool PluginWidget::onMouseMove(plugin::MouseContext mouse)
{
    return plugin_widget_i->onMouseMove(mouse);
}

bool PluginWidget::onClock(size_t delta)
{
    return plugin_widget_i->onClock(delta);
}
