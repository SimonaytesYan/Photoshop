#include "Widget.h"
#include "../Renderable.h"
#include "../../Vector/Vector.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"

Widget::Widget (Vector _position, Vector _size, bool _available) :
Renderable  (),
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
    int index = sub_widgets.Begin();
    while (index != -1)
    {
        delete sub_widgets[index].val;
        index = sub_widgets.Iterate(index);
    }
}

void Widget::Move(Vector delta)
{
    for (int i = 0; i < reg_set.GetLength(); i++)
    {
        reg_set.ChangeElem(i, ClipRegion(delta + reg_set[i].GetPosition(), 
                                reg_set[i].GetSize(), reg_set[i].GetColor()));
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
        int index = sub_widgets.Begin();
        while (index != -1)
        {
            sub_widgets[index].val->Render(render_target);

            index = sub_widgets.Iterate(index);
        }
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
    int index = objects.Begin();
    while (index != -1 && !intercepted)
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
        index = objects.Iterate(index);
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

bool Widget::OnMousePress(MouseCondition mouse)
{
    return WidgetEventRound(MOUSE_PRESS, &mouse, sub_widgets, available);
}
 
bool Widget::OnMouseRelease(MouseCondition mouse)
{
    return WidgetEventRound(MOUSE_RELEASE, &mouse, sub_widgets, available);
}

bool Widget::OnMouseMove(MouseCondition mouse)
{
    return WidgetEventRound(MOUSE_MOVE, &mouse, sub_widgets, available);
}

void Widget::UpdateRegionSet() 
{
    reg_set.Clear();
    reg_set.AddRegion(ClipRegion(position, size));      //Clear region set

    RegionSet tmp_reg;
    tmp_reg.AddRegion(ClipRegion(Vector(0, 0), Vector(0, 0)));
    for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index)) 
    {
        Widget* sub_w = sub_widgets[index].val;
        if (sub_w->available)
        {
            tmp_reg[0] = ClipRegion(ClipRegion(sub_w->position,
                                               sub_w->size));
            reg_set -= tmp_reg;
            sub_w->UpdateRegionSet();
        }
    }
}
