#include "Widget.h"
#include "../Renderable.h"
#include "../../Vec2/Vec2.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../Useful.h"

const double kPrecision = 1e-6;

Widget::Widget (plugin::Vec2 _position, plugin::Vec2 _size, bool _available) :
Renderable      (),
available       (_available),
position        (_position),
size            (_size),
sub_widgets     (List<WidgetPtr>(0)),
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
        ClipRegion reg(delta + default_reg_set[i].getPosition(), 
                       default_reg_set[i].getSize());
        default_reg_set.ChangeElem(i, reg);
    }

    for (int i = 0; i < reg_set.GetLength(); i++)
    {
        reg_set.ChangeElem(i, ClipRegion(delta + reg_set[i].getPosition(), 
                                         reg_set[i].getSize()));
    }

    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
        sub_widgets[i].val.move(delta);
}

void Widget::unregisterSubWidget(WidgetI* son)
{
    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
    {
        if (sub_widgets[index].val.is_extern && 
            sub_widgets[index].val.widget_i == son ||
            !sub_widgets[index].val.is_extern && 
            sub_widgets[index].val.widget   == son)
        {
            sub_widgets.Remove(index);
            break;
        }
    }
}

void Widget::render(plugin::RenderTargetI* render_target)
{
    if (available)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
        {
            WidgetPtr sub_widget = sub_widgets[index].val;
            if (sub_widget.getAvailable())
            {
                if (sub_widget.is_extern)
                    sub_widget.widget_i->render(render_target);
                else
                    sub_widget.widget->render(render_target);
            }
        }
    }
}

void Widget::render(RenderTarget* render_target)
{
    if (available)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
        {
            WidgetPtr sub_widget = sub_widgets[index].val;
            if (sub_widget.getAvailable())
            {
                if (sub_widget.is_extern)
                    sub_widget.widget_i->render((plugin::RenderTargetI*)render_target);
                else
                    sub_widget.widget->render(render_target);
            }
        }
    }
}

void Widget::registerSubWidget(WidgetI* new_widget)
{
    new_widget->setParent(this);
    sub_widgets.PushBack(WidgetPtr(new_widget));

    UpdateRegionSet();
}

bool WidgetEventRound(Events event, void*  event_args, 
                      List<WidgetPtr> &objects, bool available)
{
    if (!available)
        return false;

    bool intercepted = false;
    int index        = objects.End();
    while (index != -1)
    {
        switch (event)
        {
        case KEY_PRESS:
            intercepted = objects[index].val.onKeyboardPress(*(plugin::KeyboardContext*)event_args);
            break;
        case KEY_RELEASE:
            intercepted = objects[index].val.onKeyboardRelease(*(plugin::KeyboardContext*)event_args);
            break;
        case MOUSE_PRESS:
            intercepted = objects[index].val.onMousePress(*(plugin::MouseContext*)event_args);
            break;
        case MOUSE_RELEASE:
            intercepted = objects[index].val.onMouseRelease(*(plugin::MouseContext*)event_args);
            break;
        case MOUSE_MOVE:
            intercepted = objects[index].val.onMouseMove(*(plugin::MouseContext*)event_args);
            break;
        case ON_CLOCK:
            intercepted = objects[index].val.onClock(*(size_t*)event_args);
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
    return WidgetEventRound(KEY_PRESS, &key, sub_widgets, available);
}

bool Widget::onKeyboardRelease(plugin::KeyboardContext key)
{
    return WidgetEventRound(KEY_RELEASE, &key, sub_widgets, available);
}

void Widget::ToForeground(Widget* son)
{
    int index = 0;
    for (index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
    {
        if (!sub_widgets[index].val.is_extern && son == sub_widgets[index].val.widget)
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
    if (InsideP(mouse.position))
    {
        if (parent != nullptr)
            parent->ToForeground(this);
        return WidgetEventRound(MOUSE_PRESS, &mouse, sub_widgets, available);
    }
    return false;
}
 
bool Widget::onMouseRelease(plugin::MouseContext mouse)
{
    return WidgetEventRound(MOUSE_RELEASE, &mouse, sub_widgets, available);
}

bool Widget::onMouseMove(plugin::MouseContext mouse)
{
    return WidgetEventRound(MOUSE_MOVE, &mouse, sub_widgets, available);
}

bool Widget::onClock(size_t delta)
{
    return WidgetEventRound(ON_CLOCK, &delta, sub_widgets, available);
}

void Widget::UpdateRegionSet()
{
    Widget* root = this;
    while (root->parent != nullptr)
        root = root->parent;

    root->recalcRegion();
}

void Widget::recalcRegion()
{
    if (!available)
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
            if (parent->sub_widgets[index].val.widget_i == this)
                break;
        }
        
        index = parent->sub_widgets.Iterate(index);     // Skip itself
        
        // Intersect with brothers
        for (index; index != -1; index = parent->sub_widgets.Iterate(index))
        {
            WidgetPtr brother = parent->sub_widgets[index].val;
            reg_set -= brother.GetDefaultRegSet();
        }
    }

    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))  // Update children
    {
        WidgetPtr sub_w = sub_widgets[index].val;
        
        if (sub_w.getAvailable())
            sub_w.recalcRegion();
    }

    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index)) // Remove children from this
    {
        WidgetPtr sub_w = sub_widgets[index].val;
        if (sub_w.getAvailable())
            reg_set -= sub_w.GetDefaultRegSet();
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


//------------------------------------WIDGET_PTR--------------------------------

WidgetPtr::WidgetPtr(plugin::WidgetI* object)
{
    if (object->isExtern())
    {
        is_extern = true;
        widget_i  = object;
    }
    else
    {
        is_extern = false;
        widget    = (Widget*)object;
    }
}

RegionSet WidgetPtr::GetDefaultRegSet()
{
    if (is_extern)
    {
        RegionSet reg_set;
        reg_set.AddRegion(ClipRegion(widget_i->getPos(), widget_i->getSize()));
        return reg_set;   
    }
    
    return widget->GetDefaultRegSet();
}

bool WidgetPtr::onKeyboardPress(plugin::KeyboardContext key)
{
    if (is_extern)
        return widget_i->onKeyboardPress(key);
    return widget->onKeyboardPress(key);
}

bool WidgetPtr::onKeyboardRelease(plugin::KeyboardContext key)
{
    if (is_extern)
        return widget_i->onKeyboardRelease(key);
    return widget->onKeyboardRelease(key);
}

bool WidgetPtr::onMousePress(plugin::MouseContext mouse) 
{
    if (is_extern)
        return widget_i->onMousePress(mouse);
    return widget->onMousePress(mouse);
}

bool WidgetPtr::onMouseRelease(plugin::MouseContext mouse) 
{
    if (is_extern)
        return widget_i->onMouseRelease(mouse);
    return widget->onMouseRelease(mouse);
}

bool WidgetPtr::onMouseMove(plugin::MouseContext mouse) 
{
    if (is_extern)
        return widget_i->onMouseMove(mouse);
    return widget->onMouseMove(mouse);
}

bool WidgetPtr::onClock(size_t delta)       
{
    if (is_extern)
        return widget_i->onClock(delta);
    return widget->onClock(delta);
}

bool WidgetPtr::getAvailable()
{
    if (is_extern)
        return widget_i->getAvailable();
    return widget->getAvailable();
}

void WidgetPtr::recalcRegion()
{
    if (is_extern)
        return widget_i->recalcRegion();
    return widget->recalcRegion();        
}

void WidgetPtr::move(plugin::Vec2 shift)
{
    if (is_extern)
        return widget_i->move(shift);
    return widget->move(shift);
}

bool WidgetPtr::InsideP(plugin::Vec2 v)
{
    if (is_extern)
    {
        return v.GetX() - widget_i->getPos().GetX() >= 0 &&
               v.GetX() - widget_i->getPos().GetX() <= widget_i->getSize().GetX() &&
               v.GetY() - widget_i->getPos().GetY() >= 0 && 
               v.GetY() - widget_i->getPos().GetY() <= widget_i->getSize().GetY() ;
    }

    return widget->InsideP(v);
}

void WidgetPtr::setAvailable(bool value)
{
    if (is_extern)
        widget_i->setAvailable(value);
    else
        widget->setAvailable(value);
}

plugin::Vec2 WidgetPtr::getSize()
{
    if (is_extern)
        return widget_i->getSize();
    return widget->getSize();
}

plugin::Vec2 WidgetPtr::getPos()
{
    if (is_extern)
        return widget_i->getPos();
    return widget->getPos();
}
