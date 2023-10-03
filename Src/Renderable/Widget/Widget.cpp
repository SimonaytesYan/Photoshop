#include "../Renderable.h"
#include "Widget.h"
#include "../../Vector/Vector.h"

Widget::Widget (Vector _position, bool available) :
Renderable  (),
available   (available),
position    (_position),
sub_widgets (List<Widget*>(0))
{}

Widget::~Widget()
{
    fprintf(stderr, "{\nWidget dtor\n");
    int index = sub_widgets.Begin();
    while (index != -1)
    {
        delete sub_widgets[index].val;
        index = sub_widgets.Iterate(index);
    }

    fprintf(stderr, "end dtor\n}\n\n");
}

void Widget::Render(RenderTarget* render_target)
{
    if (available)
    {
        int index = sub_widgets.End();
        while (index != -1)
        {
            sub_widgets[index].val->Render(render_target);

            index = sub_widgets.Deterate(index);
        }
    }
}

void Widget::AddObject(Widget* new_widget)
{
    sub_widgets.PushFront(new_widget);
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
    int index = objects.End();
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
