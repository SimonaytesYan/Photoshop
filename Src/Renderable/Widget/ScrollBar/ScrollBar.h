#ifndef SYM_SCROLL_BAR
#define SYM_SCROLL_BAR

#include "../Widget.h"

static void MoveTarget(void* args, Vector delta)
{
    Widget* target = (Widget*)args;
    target->Move(delta);
}

class ScrollBar : public Widget
{
    bool             pressed;
    double           sensitivity;
    Color            background_color;
    RectangleWidget* slider;
    Vector           last_mouse_pos;

    void* scroll_args;
    void (*scroll)(void*, Vector);

public:
    ScrollBar(Vector _position,  Vector _size, 
              Color _background, Color _slider_color, double _sensitivity,
              void (*_scroll)(void*, Vector) = nullptr, 
              void* _scroll_args             = nullptr) :
    Widget          (_position, _size),
    background_color(_background),
    last_mouse_pos  (Vector(-1, -1)),
    scroll          (_scroll),
    scroll_args     (_scroll_args),
    sensitivity     (_sensitivity),
    pressed         (false)
    {
        slider = new RectangleWidget(_position, _size / 2, _slider_color);
        AddObject(slider);
    }

    ScrollBar(Vector _position,  Vector _size, 
              Color _background, Color _slider_color, double _sensitivity,
              Widget* target, 
              Vector visible_box_offset, Vector visible_box_size) :
    Widget          (_position, _size),
    background_color(_background),
    last_mouse_pos  (Vector(-1, -1)),
    scroll          (MoveTarget),
    scroll_args     (target)
    {
        slider = new RectangleWidget(_position, _size / 2, _slider_color);
        AddObject(slider);

        // Create interlayer between target->parent and target
        Widget* parent = target->GetParent();
        parent->RemoveSon(this);

        Widget* interlayer = new Widget(position + visible_box_offset, 
                                        visible_box_size);
        interlayer->AddObject(this);
        parent->AddObject(interlayer);
        
        scroll      = MoveTarget;
        scroll_args = this;
    }

    bool OnMouseRelease(MouseCondition mouse) override;
    bool OnMousePress  (MouseCondition mouse) override;
    bool OnMouseMove   (MouseCondition mouse) override;
    void Render        (RenderTarget* tr)     override;
};

#endif // SYM_SCROLL_BAR