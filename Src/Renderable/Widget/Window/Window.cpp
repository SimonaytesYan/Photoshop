#include "Window.h"
#include "../Button/Button.h"
#include "../Label/Label.h"
#include "../../../Constants.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

const size_t kHeaderSize      = 50;
const size_t kBorderThick     = 10;
const plugin::Color  kBorderColor     = plugin::Color(175, 200, 175);
const plugin::Color  kBackgroundColor = plugin::Color(255, 255, 255);

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

Window::Window(plugin::Vec2 _position, plugin::Vec2 _size, const char* header) :
Widget(_position, _size),
old_mouse_pos (plugin::Vec2(-1, -1)),
moving(false)
{
    Font font;
    font.LoadFont(kFontFile);
    Texture close_texture_press, close_texture;
    close_texture.LoadFromFile(kCloseImgFile);
    close_texture_press.LoadFromFile(kClosePressedImgFile);
    
    Button* header_button = new Button(position, plugin::Vec2(_size.GetX() - kHeaderSize, kHeaderSize), 
                                       kBorderColor, new ButtonMove(this)); // Button to move window

    header_button->registerSubWidget(new Label(position, font, kHeaderSize * 0.8, header, kBorderColor));    // Header
    registerSubWidget(header_button);

    plugin::Vec2 close_button_pos = plugin::Vec2(position.GetX() + size.GetX() - kHeaderSize, 
                                    position.GetY());
    registerSubWidget(new Button(close_button_pos, plugin::Vec2(kHeaderSize, kHeaderSize), 
                                 close_texture, close_texture_press,
                                 nullptr,
                                 new ButtonClose(this)));   // Button to close window
}

Window::~Window()
{
}

// new_widget add into window with border and header indent 
void Window::addIntoWindow(Widget* new_widget)
{
    plugin::Vec2 left_up_corner = new_widget->getPos() + plugin::Vec2(kBorderThick, kHeaderSize);
    if (new_widget->getPos().x < left_up_corner.GetX())
        new_widget->setPos(plugin::Vec2(left_up_corner.x, new_widget->getPos().y));
    if (new_widget->getPos().y < left_up_corner.GetY())
        new_widget->setPos(plugin::Vec2(new_widget->getPos().x, left_up_corner.y));

    plugin::Vec2 bottom_right_corner = new_widget->getPos() + plugin::Vec2(kBorderThick, kHeaderSize);
    if (new_widget->getPos().x > bottom_right_corner.GetX())
        new_widget->setPos(plugin::Vec2(bottom_right_corner.x, new_widget->getPos().y));
    if (new_widget->getPos().y > bottom_right_corner.GetY())
        new_widget->setPos(plugin::Vec2(new_widget->getPos().x, bottom_right_corner.y));

    Widget::registerSubWidget(new_widget);
}

bool Window::onMousePress(plugin::MouseContext mouse)
{
    if (available && visible)
    {
        if (InsideP(mouse.position))
        {
            Widget::onMousePress(mouse);
            return true;
        }
    }
    return false;
}

bool Window::onMouseMove(plugin::MouseContext mouse)
{
    if (moving)
    {
        if (old_mouse_pos == plugin::Vec2(-1, -1))
            old_mouse_pos = mouse.position;
        else
        {
            Widget::move(mouse.position - old_mouse_pos);
            UpdateRegionSet();

            old_mouse_pos = mouse.position;
        }
        return true;
    }

    return Widget::onMouseMove(mouse);
}

bool Window::onMouseRelease(plugin::MouseContext mouse)
{
    if (Widget::onMouseRelease(mouse))
        return true;

    if (moving)
    {
        old_mouse_pos = plugin::Vec2(-1, -1);
        moving = false;

        return true;
    }   
    return false;
}

// We can`t run destructor right here because of segfault in OnMousePress function.
// So we set available to false and 
// this object will be deleted in the nearest render pass. 
void Window::Close()
{
    available = false;
    UpdateRegionSet();
}

bool Window::InsideP(plugin::Vec2 v)
{
    return v.GetX() - position.GetX() > 0           &&
           v.GetX() - position.GetX() < size.GetX() &&
           v.GetY() - position.GetY() > 0           && 
           v.GetY() - position.GetY() < size.GetY();
}

void Window::render(RenderTarget* render_target)
{
    if (available && visible)
    {
        render_target->DrawRect(position, size, reg_set, 
                                kBackgroundColor, kBorderThick, kBorderColor);  //border + background

        Widget::render(render_target);
    }
}
