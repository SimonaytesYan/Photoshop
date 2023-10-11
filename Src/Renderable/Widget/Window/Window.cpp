#include "Window.h"
#include "../Button/Button.h"
#include "../Label/Label.h"
#include "../../../Resources.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

const size_t kButtonSize = 50;

void ButtonClose(void* args)
{
	((Window*)(args))->Close();
}

void ButtonMove(void* args)
{
    printf("go to move\n");
    ((Window*)(args))->moving = true;
    printf("((Window*)(args))->moving = %d\n", ((Window*)(args))->moving);
}

Window::Window(Vector _position, Vector _size, char* header) :
Widget(_position),
size  (_size),
old_mouse_pos (Vector(-1, -1))
{
    Font font;
    font.LoadFont(kFontFile);
    Texture texture;
    texture.LoadFromFile(kCloseImgFile);

    AddObject(new Button (position, Vector(_size.GetX() - kButtonSize, kButtonSize), 
                          Texture(), ButtonMove, (void*)this));
    AddObject(new Label  (position, font, 40, header));

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

bool Window::OnMouseMove(MouseCondition mouse)
{
    if (Widget::OnMouseMove(mouse))
        return true;

    if (moving)
    {
        if (old_mouse_pos == Vector(-1, -1))
            old_mouse_pos = mouse.position;
        else
        {
            Widget::Move(mouse.position - old_mouse_pos);
            old_mouse_pos = mouse.position;
        }
        return true;
    }
    return false;
}

bool Window::OnMouseRelease(MouseCondition mouse)
{
    if (Widget::OnMouseRelease(mouse))
        return true;

    if (moving)
    {
        printf("MouseRelease\n");
        old_mouse_pos = Vector(-1, -1);
        moving = false;

        return true;
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
                                Color(255, 255, 255), 10, Color(0, 255, 255));  //border
        render_target->DrawRect(position, 
                                Vector(size.GetX(), kButtonSize), reg_set,
                                Color(0, 255, 255));                            //header

        Widget::Render(render_target);
    }
}