#include "ScrollBar.h"
#include "../../../ClipRegion/ClipRegion.h"

bool ScrollBar::OnMouseMove(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        if (pressed)
        {
            Vector delta = (mouse.position - slider->GetPosition()) * sensitivity;

            slider->Move(delta);
            if (scroll != nullptr)
                scroll(scroll_args, delta);
        }
    }
    else
        pressed = false;
    
    return false;
}

bool ScrollBar::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        fprintf(stderr, "Inside Scroll Bar\n");
        pressed = true;
        Vector delta = (mouse.position - slider->GetPosition()) * sensitivity;
        slider->Move(delta);

        return true;
    }

    return false;
}

bool ScrollBar::OnMouseRelease(MouseCondition mouse)
{
    pressed = false;

    return false;
}

void ScrollBar::Render(RenderTarget* rt)
{
    rt->DrawRect(position, size, reg_set, background_color);

    Widget::Render(rt);
}
