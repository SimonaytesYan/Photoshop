#include "Widget.h"
#include "../Renderable.h"
#include "../../Vec2/Vec2.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../Useful.h"

const double kPrecision = 1e-6;

Widget::Widget (plugin::Vec2 _position, plugin::Vec2 _size, bool _available) :
Renderable      (),
EventProcessable(0),
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

void Widget::Move(plugin::Vec2 delta)
{
    position = position + delta;
    for (int i = 0; i < default_reg_set.GetLength(); i++)
    {
        ClipRegion reg(delta + default_reg_set[i].GetPosition(), 
                       default_reg_set[i].GetSize());
        default_reg_set.ChangeElem(i, reg);
    }

    for (int i = 0; i < reg_set.GetLength(); i++)
    {
        reg_set.ChangeElem(i, ClipRegion(delta + reg_set[i].GetPosition(), 
                                         reg_set[i].GetSize()));
    }

    for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
        sub_widgets[i].val->Move(delta);
}

void Widget::RemoveSon(Widget* son)
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

void Widget::render(RenderTargetI* render_target)
{
    if (available)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
        {
            if (sub_widgets[index].val->getAvailable())
                sub_widgets[index].val->render(render_target);
        }
    }
}

void Widget::render(RenderTarget* render_target)
{
    if (available)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
        {
            if (sub_widgets[index].val.widget_i->getAvailable())
                sub_widgets[index].val->render(render_target);
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
            intercepted = objects[index].val.onKeyboardPress(*(KeyboardContext*)event_args);
            break;
        case KEY_RELEASE:
            intercepted = objects[index].val.onKeyboardRelease(*(KeyboardContext*)event_args);
            break;
        case MOUSE_PRESS:
            intercepted = objects[index].val.onMousePress(*(MouseContext*)event_args);
            break;
        case MOUSE_RELEASE:
            intercepted = objects[index].val.onMouseRelease(*(MouseContext*)event_args);
            break;
        case MOUSE_MOVE:
            intercepted = objects[index].val.onMouseMove(*(MouseContext*)event_args);
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

bool Widget::onKeyboardPress(KeyboardContext key)
{
    return WidgetEventRound(KEY_PRESS, &key, sub_widgets, available);
}

bool Widget::onKeyboardRelease(KeyboardContext key)
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

bool Widget::onMousePress(MouseContext mouse)
{
    if (InsideP(mouse.position))
    {
        if (parent != nullptr)
            parent->ToForeground(this);
        return WidgetEventRound(MOUSE_PRESS, &mouse, sub_widgets, available);
    }
    return false;
}
 
bool Widget::onMouseRelease(MouseContext mouse)
{
    return WidgetEventRound(MOUSE_RELEASE, &mouse, sub_widgets, available);
}

bool Widget::onMouseMove(MouseContext mouse)
{
    return WidgetEventRound(MOUSE_MOVE, &mouse, sub_widgets, available);
}

bool Widget::onClock(size_t delta)
{
    return WidgetEventRound(ON_CLOCK, &delta, sub_widgets, available);
}

void Widget::UpdateRegionSet(bool debug)
{
    Widget* root = this;
    while (root->parent != nullptr)
        root = root->parent;

    root->recalcRegion(debug);
}

void Widget::recalcRegion(bool debug)
{
    if (!available)
        return;
    
    reg_set = default_reg_set;  // Set region set to default region set

    if (debug)
    {
        fprintf(stderr, "\nthis = %p\n", this);
        fprintf(stderr, "[\n");
        fprintf(stderr, "default:\n");
        default_reg_set.Dump();
        fprintf(stderr, "reg:\n");
        reg_set.Dump();
        fprintf(stderr, "]\n");
    }

    if (parent != nullptr)                              
    {
        reg_set &= parent->reg_set;                 // Intersect with parent

        if (debug)
        {
            fprintf(stderr, "after parent %p\n", parent);
            fprintf(stderr, "parent = \n");
            parent->reg_set.Dump();
            fprintf(stderr, "me = \n");
            reg_set.Dump();
        }

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

            if (debug)
            {
                fprintf(stderr, "after brother %p\n", brother);
                reg_set.Dump();
            }
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
        {
            reg_set -= sub_w->GetDefaultRegSet();

            if (debug)
            {
                fprintf(stderr, "after son %p\n", sub_w);
                reg_set.Dump();
            }
        }
    }

    if (debug)
        fprintf(stderr, "End region set update\n\n");
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
