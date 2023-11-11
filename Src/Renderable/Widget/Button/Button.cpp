#include "Button.h"
#include "../../../Vector/Vector.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"
#include "../Label/Label.h"

Button::Button(Vector _position, Vector _size, 
               Texture _texture, Texture  _press_texture,
               ButtonFunction*  _on_press,
               ButtonFunction*  _on_release) :
Widget           (_position, _size),
on_press         (_on_press),
on_release       (_on_release),
press_texture    (_press_texture),
texture          (_texture),
background_color (Color(0, 0, 0, 0)),
use_texture      (true),
pressed          (false)
{}

Button::Button(Vector _position, Vector _size, Color _background_color,
               ButtonFunction*  _on_press,
               ButtonFunction*  _on_release) :
Widget           (_position, _size),
on_press         (_on_press),
on_release       (_on_release),
press_texture    (Texture()),
texture          (Texture()),
background_color (_background_color),
use_texture      (false),
pressed          (false)
{}

Button::~Button()
{
    delete on_press;
    delete on_release;
}

void Button::Render(RenderTarget* render_target)
{
    if (available)
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
}

bool Button::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        bool intercepted = Widget::OnMousePress(mouse);

        if (!intercepted)
        {
            pressed = true;
            if (on_press == nullptr)
                return false;
            (*on_press)();      // call button function
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

            (*on_release)();
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

//==============================TEXT BUTTON=========================

TextButton::TextButton(Vector   position, Vector  size, 
                       Texture  texture, Texture  press_texture,
                       Font font, int character_size, const char* text,
                       Color text_color, Color background_color,
                       ButtonFunction*  _on_press,
                       ButtonFunction*  _on_release) : 
Button(position, size, texture, press_texture, _on_press, _on_release)
{
    AddObject(new Label(position, font, character_size, text, background_color, text_color));
}
    
TextButton::TextButton(Vector   position,  Vector   size, 
                       Color    background_color,
                       Font font, int character_size, const char* text,
                       Color text_color,
                       ButtonFunction*  _on_press,
                       ButtonFunction*  _on_release) :
Button(position, size, background_color, _on_press, _on_release)
{
    AddObject(new Label(position, font, character_size, text, background_color, text_color));
}