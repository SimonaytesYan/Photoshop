#include "Window.h"

Window::Window(Vector _position, Vector _size) :
Widget(_position),
size  (_size)
{
}

bool Window::OnMousePress(MouseCondition mouse)
{
    if (Inside_p(mouse.position))
    {
        Widget::OnMousePress(mouse);
        return true;
    }
    
    return false;
}

void Window::Close()
{
    available = false;
}

bool Window::Inside_p(Vector v)
{
    return v.GetX() - position.GetX() > 0           &&
           v.GetX() - position.GetX() < size.GetX() &&
           v.GetY() - position.GetY() > 0           && 
           v.GetY() - position.GetY() < size.GetY();
}

void Window::Render(RenderTarget* render_target)
{
    if (available)
        Widget::Render(render_target);
}