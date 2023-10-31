#include "Window.h"
#include "../Button/Button.h"
#include "../Label/Label.h"
#include "../../../Resources.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

const size_t kButtonSize      = 50;
const size_t kBorderThick     = 10;
const Color  kBorderColor     = Color(175, 200, 175); //Color(0,   255, 255);
const Color  kBackgroundColor = Color(255, 255, 255);

void ButtonClose(void* args)
{
	((Window*)(args))->Close();
}

void ButtonMove(void* args)
{
    ((Window*)(args))->moving = true;
}

Window::Window(Vector _position, Vector _size, const char* header) :
Widget(_position, _size),
old_mouse_pos (Vector(-1, -1)),
moving(false)
{
    Font font;
    font.LoadFont(kFontFile);
    Texture close_texture_press, close_texture;
    close_texture.LoadFromFile(kCloseImgFile);
    close_texture_press.LoadFromFile(kClosePressedImgFile);

    Button* header_button = new Button(position, Vector(_size.GetX() - kButtonSize, kButtonSize), 
                                       kBorderColor, ButtonMove, (void*)this);         //Button to move window

    header_button->AddObject(new Label(position, font, 40, header, kBorderColor));    //Header
    AddObject(header_button);

    Vector close_button_pos = Vector(position.GetX() + size.GetX() - kButtonSize, 
                                    position.GetY());
    AddObject(new Button(close_button_pos, Vector(kButtonSize, kButtonSize), 
                         close_texture, close_texture_press,
                         nullptr, nullptr,
                         ButtonClose, (void*)this));                       //Close button window
}

Window::~Window()
{
}

bool Window::OnMousePress(MouseCondition mouse)
{
    if (available)
    {
        if (InsideP(mouse.position))
        {
            Widget::OnMousePress(mouse);
            return true;
        }
    }
    return false;
}

bool Window::OnMouseMove(MouseCondition mouse)
{
    if (moving)
    {
        if (old_mouse_pos == Vector(-1, -1))
            old_mouse_pos = mouse.position;
        else
        {
            Widget::Move(mouse.position - old_mouse_pos);

            if (parent != nullptr)
                parent->UpdateRegionSet();

            old_mouse_pos = mouse.position;
        }
        return true;
    }

    return Widget::OnMouseMove(mouse);
}

bool Window::OnMouseRelease(MouseCondition mouse)
{
    if (Widget::OnMouseRelease(mouse))
        return true;

    if (moving)
    {
        old_mouse_pos = Vector(-1, -1);
        moving = false;

        return true;
    }   
    return false;
}

void Window::Close()
{
    available = false;
    size = Vector(0, 0);
    if (parent != nullptr)
        parent->UpdateRegionSet();
    
    this->~Window();
}

bool Window::InsideP(Vector v)
{
    return v.GetX() - position.GetX() > 0           &&
           v.GetX() - position.GetX() < size.GetX() &&
           v.GetY() - position.GetY() > 0           && 
           v.GetY() - position.GetY() < size.GetY();
}

void Window::Render(RenderTarget* render_target)
{
    if (available)
    {
        render_target->DrawRect(position, size, reg_set, 
                                kBackgroundColor, kBorderThick, kBorderColor);  //border + background

        Widget::Render(render_target);
    }
}