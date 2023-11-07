#include "ScrollBar.h"
#include "../../../ClipRegion/ClipRegion.h"

bool ScrollBar::OnMouseMove(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        if (pressed)
        {
            Vector delta = (mouse.position - last_mouse_pos) * sensitivity;

            slider->Move(delta);
            UpdateRegionSet();
            if (scroll != nullptr)
                scroll(scroll_args, delta);
            
            last_mouse_pos = mouse.position;
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
        pressed = true;
        last_mouse_pos = mouse.position;
        if (!slider->InsideP(mouse.position))
        {
            Vector delta = (mouse.position - slider->GetPosition()) * sensitivity;
            slider->Move(delta);
            UpdateRegionSet();
        }

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
