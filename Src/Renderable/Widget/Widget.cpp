#include "Widget.h"
#include "../Renderable.h"
#include "../../Vector/Vector.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../Useful.h"

Widget::Widget (Vector _position, Vector _size, bool _available) :
Renderable      (),
EventProcessable(0),
available   (_available),
position    (_position),
size        (_size),
sub_widgets (List<Widget*>(0)),
reg_set     (RegionSet()),
parent      (nullptr)
{
    reg_set.AddRegion(ClipRegion(_position, _size));
}

Widget::~Widget()
{
}

void Widget::Move(Vector delta)
{
    for (int i = 0; i < reg_set.GetLength(); i++)
    {
        reg_set.ChangeElem(i, ClipRegion(delta + reg_set[i].GetPosition(), 
                                         reg_set[i].GetSize()));
    }
    position = position + delta;

    int index = sub_widgets.Begin();
    while (index != -1)
    {
        sub_widgets[index].val->Move(delta);

        index = sub_widgets.Iterate(index);
    }
}

void Widget::Render(RenderTarget* render_target)
{
    if (available)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
            sub_widgets[index].val->Render(render_target);
    }
}

void Widget::AddObject(Widget* new_widget)
{
    new_widget->parent = this;
    sub_widgets.PushBack(new_widget);

    UpdateRegionSet();
}

Vector Widget::GetPosition()
{
    return position;
}

bool WidgetEventRound(Events event, void*  event_args, 
                      List<Widget*> &objects, bool available)
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
            intercepted = objects[index].val->OnKeyPress(*(Key*)event_args);
            break;
        case KEY_RELEASE:
            intercepted = objects[index].val->OnKeyRelease(*(Key*)event_args);
            break;
        case MOUSE_PRESS:
            intercepted = objects[index].val->OnMousePress(*(MouseCondition*)event_args);
            break;
        case MOUSE_RELEASE:
            intercepted = objects[index].val->OnMouseRelease(*(MouseCondition*)event_args);
            break;
        case MOUSE_MOVE:
            intercepted = objects[index].val->OnMouseMove(*(MouseCondition*)event_args);
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

bool Widget::OnKeyPress(Key key)
{
    return WidgetEventRound(KEY_PRESS, &key, sub_widgets, available);
}

bool Widget::OnKeyRelease(Key key)
{
    return WidgetEventRound(KEY_RELEASE, &key, sub_widgets, available);
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

bool Widget::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        if (parent != nullptr)
            parent->ToForeground(this);
        return WidgetEventRound(MOUSE_PRESS, &mouse, sub_widgets, available);
    }
    return false;
}
 
bool Widget::OnMouseRelease(MouseCondition mouse)
{
    return WidgetEventRound(MOUSE_RELEASE, &mouse, sub_widgets, available);
}

bool Widget::OnMouseMove(MouseCondition mouse)
{
    return WidgetEventRound(MOUSE_MOVE, &mouse, sub_widgets, available);
}

void Widget::UpdateRegionSet(bool debug)
{
    Widget* root = this;
    while (root->parent != nullptr)
        root = root->parent;

    root->UpdateRegionSetFromRoot(debug);
}

void Widget::UpdateRegionSetFromRoot(bool debug)
{
    if (!available)
        return;
        
    reg_set.Clear();
    reg_set.AddRegion(ClipRegion(position, size));      // Clear region set

    if (debug)
    {
        fprintf(stderr, "\nthis = %p\n", this);
        reg_set.Dump();
    }

    RegionSet tmp_rs;
    tmp_rs.AddRegion(ClipRegion(Vector(0, 0), Vector(0, 0)));

    if (parent != nullptr)                              
    {
        reg_set &= parent->reg_set;                 // Intersect with parent

        if (debug)
        {
            fprintf(stderr, "after parent %p\n", parent);
            fprintf(stderr, "parent = ");
            parent->reg_set.Dump();
            fprintf(stderr, "me = \n");
            reg_set.Dump();
        }

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
            tmp_rs[0] = ClipRegion(brother->position, brother->size);
            reg_set -= tmp_rs;

            if (debug)
            {
                fprintf(stderr, "after brother %p\n", brother);
                reg_set.Dump();
            }
        }
    }

    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))  // Update children
    {
        Widget* sub_w = sub_widgets[index].val;
        
        if (sub_w->available)
        {
            sub_w->UpdateRegionSetFromRoot(debug);
        }
    }

    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index)) // Remove children from this
    {
        Widget* sub_w = sub_widgets[index].val;
        if (sub_w->available)
        {
            tmp_rs[0] = ClipRegion(sub_w->position, sub_w->size);
            reg_set -= tmp_rs;

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

bool Widget::InsideP(Vector v)
{
    return v.GetX() - position.GetX() > 0           &&
           v.GetX() - position.GetX() < size.GetX() &&
           v.GetY() - position.GetY() > 0           && 
           v.GetY() - position.GetY() < size.GetY();
}
