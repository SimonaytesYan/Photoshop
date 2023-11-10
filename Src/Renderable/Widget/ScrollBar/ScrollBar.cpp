#include "ScrollBar.h"
#include "../../../ClipRegion/ClipRegion.h"

// Change delta if delta move child from parent
Vector FixDelta(const Widget& parent, const Widget& slider, Vector delta)
{
    Vector v0 = delta + slider.GetPosition();
    Vector v1 = v0 + slider.GetSize();

    if (v0.GetX() < parent.GetPosition().GetX())
        delta = Vector((parent.GetPosition() - slider.GetPosition()).GetX(), 
                       delta.GetY());
    if (v0.GetY() < parent.GetPosition().GetY())
        delta = Vector(delta.GetX(),
                       (parent.GetPosition() - slider.GetPosition()).GetY());

    if (v1.GetX() > (parent.GetPosition() + parent.GetSize()).GetX())
        delta = Vector((parent.GetPosition() + parent.GetSize() - 
                        (slider.GetPosition() + slider.GetSize())).GetX(), 
                       delta.GetY());
    if (v1.GetY() > (parent.GetPosition() + parent.GetSize()).GetY())
        delta = Vector(delta.GetX(),
                       (parent.GetPosition() + parent.GetSize() - 
                        (slider.GetPosition() + slider.GetSize())).GetY());

    return delta;
}

Vector CalcDelta(MouseCondition mouse, Vector last_mouse_pos, 
                 Widget* slider, Widget* scroll_bar)
{
    Vector delta((mouse.position - last_mouse_pos).GetX(),
                 (mouse.position - last_mouse_pos).GetY());
    delta = FixDelta(*scroll_bar, *slider, delta);

    return delta;
}

bool ScrollBar::OnMouseMove(MouseCondition mouse)
{
    if (pressed)
    {
        Vector delta = CalcDelta(mouse, last_mouse_pos, slider, this);

        slider->Move(delta);
        UpdateRegionSet();
        if (scroll != nullptr)
        {
            scroll(scroll_args, Vector(delta.GetX() * sensitivity.GetX(), 
                                       delta.GetY() * sensitivity.GetY()));
        }

        last_mouse_pos = mouse.position;
    }
    
    return false;
}

bool ScrollBar::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        fprintf(stderr, "Click inside scrollbar\n");
        pressed        = true;
        last_mouse_pos = mouse.position;
        if (!slider->InsideP(mouse.position))
        {
            Vector delta = CalcDelta(mouse, sensitivity, slider, this);
            UpdateRegionSet();
            if (scroll != nullptr)
            {
                scroll(scroll_args, Vector(delta.GetX()  * sensitivity.GetY(), 
                                           delta.GetY() * sensitivity.GetY()));
            }
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
