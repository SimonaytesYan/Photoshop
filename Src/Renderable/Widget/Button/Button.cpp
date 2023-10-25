#include "Button.h"
#include "../../../Vector/Vector.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

Button::Button(Vector _position, Vector _size, 
               Texture _texture, Texture  _press_texture,
               void  (*_on_press)  (void*), void* _args_press,  
               void  (*_on_release)(void*), void* _args_release) :
Widget           (_position, _size),
on_press         (_on_press),
args_press       (_args_press),
on_release       (_on_release),
args_release     (_args_release),
press_texture    (_press_texture),
texture          (_texture),
background_color (Color(0, 0, 0, 0)),
use_texture      (true),
pressed          (false)
{}

Button::Button(Vector _position, Vector _size, Color _background_color,
               void  (*_on_press)  (void*), void* _args_press,  
               void  (*_on_release)(void*), void* _args_release) :
Widget           (_position, _size),
on_press         (_on_press),
args_press       (_args_press),
on_release       (_on_release),
args_release     (_args_release),
press_texture    (Texture()),
texture          (Texture()),
background_color (_background_color),
use_texture      (false),
pressed          (false)
{}

Button::~Button()
{}

void Button::Render(RenderTarget* render_target)
{
    if (use_texture)
    {
        if (pressed)
            render_target->DrawSprite(position, press_texture, reg_set);
        else
            render_target->DrawSprite(position, texture, reg_set);
    }
    else
    {
        if (pressed)
            render_target->DrawRect(position, size, reg_set, background_color.Inverse());
        else
            render_target->DrawRect(position, size, reg_set, background_color);
    }

    Widget::Render(render_target);
}

bool Button::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        bool intercepted = Widget::OnMousePress(mouse);

        if (!intercepted)
        {
            pressed = true;
            printf("pressed = %d\n", pressed);
            if (on_press == nullptr)
                return false;

            on_press(args_press);   // call button function 
        }

        return true;
    }
    
    return false;
}

bool Button::OnMouseRelease(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        bool intercepted = Widget::OnMouseRelease(mouse);

        if (!intercepted)
        {
            pressed = false;
            if (on_release == nullptr)
                return false;

            on_release(args_release);
        }

        return true;
    }
    
    return false;
}

bool Button::OnMouseMove(MouseCondition mouse)
{
    if (!InsideP(mouse.position))
    {
        pressed = false;
    }
    return false;
}
