#ifndef SYM_SCROLL_BAR
#define SYM_SCROLL_BAR

#include "../Widget.h"

class Interlayer : public Widget
{
public :
    Interlayer(Vector position, Vector size) :
    Widget(position, size)
    {
    }

    bool OnMouseMove(MouseCondition mouse)    override
    {
        if (InsideP(mouse.position))
            return Widget::OnMouseMove(mouse);
        return false;
    }

    bool OnMousePress(MouseCondition mouse)   override
    {
        if (InsideP(mouse.position))
            return Widget::OnMousePress(mouse);
        return false;
    }

};

static void MoveTarget(void* args, Vector delta)
{
    Widget* target = (Widget*)args;
    target->Move(-delta);

    target->UpdateRegionSet();
}

class ScrollBar : public Widget
{
    bool             pressed;
    Vector           sensitivity;
    Color            background_color;
    RectangleWidget* slider;
    Vector           last_mouse_pos;

    void* scroll_args;
    void (*scroll)(void*, Vector);

public:
    ScrollBar(Vector _position,  Vector _size, 
              Color _background, Color _slider_color,
              void (*_scroll)(void*, Vector) = nullptr, 
              void* _scroll_args             = nullptr) :
    Widget          (_position, _size),
    background_color(_background),
    last_mouse_pos  (Vector(-1, -1)),
    scroll          (_scroll),
    scroll_args     (_scroll_args),
    pressed         (false)
    {
        // Create slider

        slider = new RectangleWidget(position, size / 2, _slider_color);
        AddObject(slider);

        // Calculate sens 
        
        double x_sens = 0;
        if ((size - slider->GetSize()).GetX() != 0)
            x_sens = size.GetX() / (size - slider->GetSize()).GetX();
        double y_sens = 0;
        if ((size - slider->GetSize()).GetY() != 0)
            y_sens = size.GetY() / (size - slider->GetSize()).GetY();

        sensitivity = Vector(x_sens, y_sens);
    }

    ScrollBar(Vector _position,  Vector _size, 
              Color _background, Color _slider_color,
              Widget* target, 
              Vector visible_box_offset, Vector visible_box_size) :
    Widget          (_position, _size),
    background_color(_background),
    last_mouse_pos  (Vector(-1, -1)),
    scroll          (MoveTarget),
    scroll_args     (target),
    pressed         (false)
    {
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

        sensitivity = Vector(x_sens, y_sens);

        // Create slider
        slider = new RectangleWidget(_position, _size / 2, _slider_color);
        AddObject(slider);

        // Create interlayer between target->parent and target
        Widget* parent = target->GetParent();
        parent->RemoveSon(target);

        Interlayer* interlayer = new Interlayer(target->GetPosition() + visible_box_offset, 
                                                visible_box_size);
        interlayer->AddObject(target);
        parent->AddObject(interlayer);
        
        scroll      = MoveTarget;
        scroll_args = target;
    }

    bool OnMouseRelease(MouseCondition mouse) override;
    bool OnMousePress  (MouseCondition mouse) override;
    bool OnMouseMove   (MouseCondition mouse) override;
    void Render        (RenderTarget* tr)     override;
};

#endif // SYM_SCROLL_BAR