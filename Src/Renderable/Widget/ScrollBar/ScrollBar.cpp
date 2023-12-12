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
    registerSubWidget(slider);

    // Calculate sens     
    double x_sens = 0;
    if ((size - slider->getSize()).GetX() != 0)
        x_sens = size.GetX() / (size - slider->getSize()).GetX();
    double y_sens = 0;
    if ((size - slider->getSize()).GetY() != 0)
        y_sens = size.GetY() / (size - slider->getSize()).GetY();

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
    registerSubWidget(slider);
        
    // Calculate sens 
    double x_sens = 0;
    if ((target->getSize() - visible_box_size).GetX() > 0 &&
        (size - slider->getSize()).GetX() > 0)
        x_sens = ((target->getSize() - visible_box_size).GetX()) / 
                 (size - slider->getSize()).GetX();

    double y_sens = 0;
    if ((target->getSize() - visible_box_size).GetY() > 0 && 
        (size - slider->getSize()).GetY() > 0)
        y_sens = (target->getSize() - visible_box_size).GetY() / 
                 (size - slider->getSize()).GetY();

    sensitivity = plugin::Vec2(x_sens, y_sens);

    // Create interlayer between target->parent and target
    plugin::WidgetI* parent = target->getParent();
    parent->unregisterSubWidget(target);

    Interlayer* interlayer = new Interlayer(target->getPos() + visible_box_offset, 
                                            visible_box_size);
    interlayer->registerSubWidget(target);
    parent->registerSubWidget(interlayer);
}

// Change delta if delta move child from parent
plugin::Vec2 FixDelta(const Widget& parent, const Widget& slider, plugin::Vec2 delta)
{
    plugin::Vec2 v0 = delta + slider.getPos();
    plugin::Vec2 v1 = v0 + slider.getSize();

    if (v0.GetX() < parent.getPos().GetX())
        delta = plugin::Vec2((parent.getPos() - slider.getPos()).GetX(), 
                       delta.GetY());
    if (v0.GetY() < parent.getPos().GetY())
        delta = plugin::Vec2(delta.GetX(),
                       (parent.getPos() - slider.getPos()).GetY());

    if (v1.GetX() > (parent.getPos() + parent.getSize()).GetX())
        delta = plugin::Vec2((parent.getPos() + parent.getSize() - 
                        (slider.getPos() + slider.getSize())).GetX(), 
                       delta.GetY());
    if (v1.GetY() > (parent.getPos() + parent.getSize()).GetY())
        delta = plugin::Vec2(delta.GetX(),
                       (parent.getPos() + parent.getSize() - 
                        (slider.getPos() + slider.getSize())).GetY());

    return delta;
}

plugin::Vec2 CalcDelta(plugin::MouseContext mouse, plugin::Vec2 last_mouse_pos, 
                       Widget* slider, Widget* scroll_bar)
{
    plugin::Vec2 delta((mouse.position - last_mouse_pos).GetX(),
                       (mouse.position - last_mouse_pos).GetY());
    delta = FixDelta(*scroll_bar, *slider, delta);

    return delta;
}

bool ScrollBar::onMouseMove(plugin::MouseContext mouse)
{
    if (pressed)
    {
        plugin::Vec2 delta = CalcDelta(mouse, last_mouse_pos, slider, this);

        slider->move(delta);
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

bool ScrollBar::onMousePress(plugin::MouseContext mouse)
{
    if (InsideP(mouse.position))
    {
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

bool ScrollBar::onMouseRelease(plugin::MouseContext mouse)
{
    pressed = false;
    return false;
}

ScrollBar::~ScrollBar()
{
    delete scroll;
}

void ScrollBar::render(RenderTarget* rt)
{
    rt->DrawRect(position, size, reg_set, background_color);

    Widget::render(rt);
}
