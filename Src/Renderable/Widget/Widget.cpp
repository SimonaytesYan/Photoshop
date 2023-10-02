#include "../Renderable.h"
#include "Widget.h"
#include "../../Vector/Vector.h"

Widget::Widget (Vector _position) :
Renderable(),
position (_position),
sub_widgets (List<Widget*>(0))
{}

Widget::~Widget()
{
    sub_widgets.~List();
}

void Widget::Render(RenderTarget* render_target)
{
    int index = sub_widgets.End();
    while (index != -1)
    {
        sub_widgets[index].val->Render(render_target);

        index = sub_widgets.Deterate(index);
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

bool Widget::OnKeyPress(Key key)
{
    int index = sub_widgets.End();
    while (index != -1)
    {
        sub_widgets[index].val->OnKeyPress(key);
        index = sub_widgets.Deterate(index);
    }
}

bool Widget::OnKeyRelease(Key key)
{
    int index = sub_widgets.End();
    while (index != -1)
    {
        sub_widgets[index].val->OnKeyRelease(key);
        index = sub_widgets.Deterate(index);
    }
}

bool Widget::OnMousePress(Vector position, MouseKey key)
{
    int index = sub_widgets.End();
    while (index != -1)
    {
        sub_widgets[index].val->OnMousePress(position, key);
        index = sub_widgets.Deterate(index);
    }

}
 
bool Widget::OnMouseRelease(Vector position, MouseKey key)
{
    int index = sub_widgets.End();
    while (index != -1)
    {
        sub_widgets[index].val->OnMouseRelease(position, key);
        index = sub_widgets.Deterate(index);
    }
}

bool Widget::OnMouseMove(Vector position, MouseKey key)
{
    int index = sub_widgets.End();
    while (index != -1)
    {
        sub_widgets[index].val->OnMouseMove(position, key);
        index = sub_widgets.Deterate(index);
    }
}

