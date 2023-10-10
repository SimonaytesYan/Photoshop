#include "Window.h"
#include "../Button/Button.h"
#include "../Label/Label.h"
#include "../../../Resources.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

const size_t kButtonSize   = 50;

void ButtonClose(void* args)
{
	((Window*)(args))->Close();
}

Window::Window(Vector _position, Vector _size, char* header) :
Widget(_position),
size  (_size)
{
    Font font;
    font.LoadFont(kFontFile);
    Texture texture;
    texture.LoadFromFile(kCloseImgFile);

    AddObject(new Label (position, font, 40, header));

    Vector button_position = Vector(position.GetX() + size.GetX() - kButtonSize, 
                                    position.GetY());

    AddObject(new Button(button_position, Vector(kButtonSize, kButtonSize), 
                         texture, ButtonClose, (void*)this));

    reg_set.AddRegion(ClipRegion(_position, _size));
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

void Window::Close()
{
    available = false;
    //this->~Window();
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
                                Color(0, 0, 0, 0), 10, Color(0, 255, 255));  //border

        render_target->DrawRect(position, size, reg_set);        //background
        render_target->DrawRect(position, 
                                Vector(size.GetX(), kButtonSize), reg_set,
                                Color(0, 255, 255));    //header


        Widget::Render(render_target);
    }
}