#include "ScrollBar.h"
#include "../../../ClipRegion/ClipRegion.h"

ScrollBar::ScrollBar(plugin::Vec2 _position,  plugin::Vec2 _size, 
                     plugin::Color _background, plugin::Color _slider_color,
                     plugin::Vec2 _slider_size,
                     ScrollBarFunction* _scroll) :
Widget          (_position, _size),
background_color(_background),
last_mouse_pos  (plugin::Vec2(-1, -1)),
scroll          (_scroll),
pressed         (false)
{
    // Create slider

    slider = new RectangleWidget(position, 
                                 plugin::Vec2(size.GetX() * _slider_size.GetX(), 
                                        size.GetY() * _slider_size.GetY()), 
                                 _slider_color);
    AddObject(slider);

    // Calculate sens     
    double x_sens = 0;
    if ((size - slider->GetSize()).GetX() != 0)
        x_sens = size.GetX() / (size - slider->GetSize()).GetX();
    double y_sens = 0;
    if ((size - slider->GetSize()).GetY() != 0)
        y_sens = size.GetY() / (size - slider->GetSize()).GetY();

    sensitivity = plugin::Vec2(x_sens, y_sens);
}

ScrollBar::ScrollBar(plugin::Vec2 _position,  plugin::Vec2 _size, 
                     plugin::Color _background, plugin::Color _slider_color,
                     plugin::Vec2 _slider_size,
                     Widget* target, 
                     plugin::Vec2 visible_box_offset, plugin::Vec2 visible_box_size) :
Widget          (_position, _size),
background_color(_background),
last_mouse_pos  (plugin::Vec2(-1, -1)),
scroll          (new MoveTarget(target)),
pressed         (false)
{
    // Create slider
    slider = new RectangleWidget(position, 
                                 plugin::Vec2(size.GetX() * _slider_size.GetX(), 
                                        size.GetY() * _slider_size.GetY()), 
                                 _slider_color);
    AddObject(slider);
        
    // Calculate sens 
    double x_sens = 0;
    if ((target->GetSize() - visible_box_size).GetX() > 0 &&
        (size - slider->GetSize()).GetX() > 0)
        x_sens = ((target->GetSize() - visible_box_size).GetX()) / 
                 (size - slider->GetSize()).GetX();

    double y_sens = 0;
    if ((target->GetSize() - visible_box_size).GetY() > 0 && 
        (size - slider->GetSize()).GetY() > 0)
        y_sens = (target->GetSize() - visible_box_size).GetY() / 
                 (size - slider->GetSize()).GetY();

    sensitivity = plugin::Vec2(x_sens, y_sens);

    // Create interlayer between target->parent and target
    Widget* parent = target->GetParent();
    parent->RemoveSon(target);

    Interlayer* interlayer = new Interlayer(target->GetPosition() + visible_box_offset, 
                                            visible_box_size);
    interlayer->AddObject(target);
    parent->AddObject(interlayer);
}

// Change delta if delta move child from parent
plugin::Vec2 FixDelta(const Widget& parent, const Widget& slider, plugin::Vec2 delta)
{
    plugin::Vec2 v0 = delta + slider.GetPosition();
    plugin::Vec2 v1 = v0 + slider.GetSize();

    if (v0.GetX() < parent.GetPosition().GetX())
        delta = plugin::Vec2((parent.GetPosition() - slider.GetPosition()).GetX(), 
                       delta.GetY());
    if (v0.GetY() < parent.GetPosition().GetY())
        delta = plugin::Vec2(delta.GetX(),
                       (parent.GetPosition() - slider.GetPosition()).GetY());

    if (v1.GetX() > (parent.GetPosition() + parent.GetSize()).GetX())
        delta = plugin::Vec2((parent.GetPosition() + parent.GetSize() - 
                        (slider.GetPosition() + slider.GetSize())).GetX(), 
                       delta.GetY());
    if (v1.GetY() > (parent.GetPosition() + parent.GetSize()).GetY())
        delta = plugin::Vec2(delta.GetX(),
                       (parent.GetPosition() + parent.GetSize() - 
                        (slider.GetPosition() + slider.GetSize())).GetY());

    return delta;
}

plugin::Vec2 CalcDelta(MouseContext mouse, plugin::Vec2 last_mouse_pos, 
                 Widget* slider, Widget* scroll_bar)
{
    plugin::Vec2 delta((mouse.position - last_mouse_pos).GetX(),
                 (mouse.position - last_mouse_pos).GetY());
    delta = FixDelta(*scroll_bar, *slider, delta);

    return delta;
}

bool ScrollBar::onMouseMove(MouseContext mouse)
{
    if (pressed)
    {
        plugin::Vec2 delta = CalcDelta(mouse, last_mouse_pos, slider, this);

        slider->Move(delta);
        UpdateRegionSet();
        if (scroll != nullptr)
        {
            scroll->delta = plugin::Vec2(delta.GetX() * sensitivity.GetX(), 
                                   delta.GetY() * sensitivity.GetY());
            (*scroll)();
        }

        last_mouse_pos = mouse.position;
    }
    
    return false;
}

bool ScrollBar::onMousePress(MouseContext mouse)
{
    if (InsideP(mouse.position))
    {
        fprintf(stderr, "Click inside scrollbar\n");
        pressed        = true;
        last_mouse_pos = mouse.position;
        if (!slider->InsideP(mouse.position))
        {
            plugin::Vec2 delta = CalcDelta(mouse, sensitivity, slider, this);
            UpdateRegionSet();
            if (scroll != nullptr)
            {
                scroll->delta = plugin::Vec2(delta.GetX() * sensitivity.GetX(), 
                                       delta.GetY() * sensitivity.GetY());
                (*scroll)();
            }
        }

        return true;
    }

    return false;
}

bool ScrollBar::onMouseRelease(MouseContext mouse)
{
    pressed = false;
    return false;
}

ScrollBar::~ScrollBar()
{
    delete scroll;
}

void ScrollBar::Render(RenderTarget* rt)
{
    rt->DrawRect(position, size, reg_set, background_color);

    Widget::Render(rt);
}
