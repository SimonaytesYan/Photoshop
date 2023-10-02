#include "Button.h"

#include "../../../Vector/Vector.h"

Button::Button(Vector _position, Vector _size, Texture _texture, 
              void  (*_on_click)(void*), void* _args) :
Widget   (_position),
size     (_size),
on_click (_on_click),
args     (_args),
texture  (_texture)
{}

void Button::Render(RenderTarget* render_target)
{
    render_target->DrawSprite(position, texture);

    Widget::Render(render_target);
}

bool Button::OnMousePress(MouseCondition mouse)
{
    if (Inside_p(mouse.position))
    {
        bool intercepted = Widget::OnMousePress(mouse);

        if (!intercepted)
        {
            if (on_click == nullptr)
                return false;

            on_click(args);
        }

        return true;
    }
    
    return false;
}

bool Button::Inside_p (Vector v)
{
    return v.GetX() - position.GetX() > 0           &&
           v.GetX() - position.GetX() < size.GetX() &&
           v.GetY() - position.GetY() > 0           && 
           v.GetY() - position.GetY() < size.GetY();
}
