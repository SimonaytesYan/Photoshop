#include "Button.h"

#include "../../../Vector/Vector.h"

Button::Button(Vector _position, Vector _size, Color _color, 
              void* _on_click, void* _args) :
Widget   (_position),
size     (_size),
color    (_color),
on_click (_on_click),
args     (_args)
{}

void Button::Render(RenderTarget* render_target)
{
    render_target->DrawRect(position, size, color);

    Widget::Render(render_target);
}
