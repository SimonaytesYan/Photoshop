#include "Button.h"
#include "../../../Vector/Vector.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

Button::Button(Vector _position, Vector _size, Texture _texture, 
              void  (*_on_click)(void*), void* _args) :
Widget   (_position),
size     (_size),
on_click (_on_click),
args     (_args),
texture  (_texture)
{
    reg_set.AddRegion(ClipRegion(_position, _size));
}

Button::~Button()
{}

void Button::Render(RenderTarget* render_target)
{
    render_target->DrawSprite(position, texture, reg_set);

    Widget::Render(render_target);
}

bool Button::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position))
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

bool Button::InsideP (Vector v)
{
    return v.GetX() - position.GetX() > 0           &&
           v.GetX() - position.GetX() < size.GetX() &&
           v.GetY() - position.GetY() > 0           && 
           v.GetY() - position.GetY() < size.GetY();
}
