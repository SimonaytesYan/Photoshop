#include "Window.h"
#include "../Button/Button.h"
#include "../Label/Label.h"
#include "../../../Constants.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

const size_t kButtonSize      = 50;
const size_t kBorderThick     = 10;
const Color  kBorderColor     = Color(175, 200, 175); //Color(0,   255, 255);
const Color  kBackgroundColor = Color(255, 255, 255);

struct ButtonMove : ButtonFunction
{
    Window* window;

    ButtonMove() {}
    ButtonMove(Window* window) : 
    window (window) 
    {}

    void operator()() override
    {
        window->SetMoving(true);
    }
};

struct ButtonClose : ButtonFunction
{
    Window* window;

    ButtonClose() {}
    ButtonClose(Window* window) : 
    window (window) 
    {}

    void operator()() override
    {
        window->Close();
    }
};

Window::Window(Vec2 _position, Vec2 _size, const char* header) :
Widget(_position, _size),
old_mouse_pos (Vec2(-1, -1)),
moving(false)
{
    Font font;
    font.LoadFont(kFontFile);
    Texture close_texture_press, close_texture;
    close_texture.LoadFromFile(kCloseImgFile);
    close_texture_press.LoadFromFile(kClosePressedImgFile);
    
    Button* header_button = new Button(position, Vec2(_size.GetX() - kButtonSize, kButtonSize), 
                                       kBorderColor, new ButtonMove(this));         //Button to move window

    header_button->AddObject(new Label(position, font, 40, header, kBorderColor));    //Header
    AddObject(header_button);

    Vec2 close_button_pos = Vec2(position.GetX() + size.GetX() - kButtonSize, 
                                    position.GetY());
    AddObject(new Button(close_button_pos, Vec2(kButtonSize, kButtonSize), 
                         close_texture, close_texture_press,
                         nullptr,
                         new ButtonClose(this)));                       //Close button window
}

Window::~Window()
{
}

bool Window::OnMousePress(MouseContext mouse)
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

bool Window::OnMouseMove(MouseContext mouse)
{
    if (moving)
    {
        if (old_mouse_pos == Vec2(-1, -1))
            old_mouse_pos = mouse.position;
        else
        {
            Widget::Move(mouse.position - old_mouse_pos);
            UpdateRegionSet();

            old_mouse_pos = mouse.position;
        }
        return true;
    }

    return Widget::OnMouseMove(mouse);
}

bool Window::OnMouseRelease(MouseContext mouse)
{
    if (Widget::OnMouseRelease(mouse))
        return true;

    if (moving)
    {
        old_mouse_pos = Vec2(-1, -1);
        moving = false;

        return true;
    }   
    return false;
}

void Window::Close()
{
    available = false;
    size = Vec2(0, 0);
    if (parent != nullptr)
    {
        parent->RemoveSon(this);
        parent->UpdateRegionSet();
    }
    
    this->~Window();
}

bool Window::InsideP(Vec2 v)
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