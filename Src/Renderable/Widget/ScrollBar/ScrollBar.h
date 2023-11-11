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

    bool OnMousePress(MouseCondition mouse)   override
    {
        if (InsideP(mouse.position))
            return Widget::OnMousePress(mouse);
        return false;
    }

};

struct ScrollBarFunction 
{
    Vector delta;
    virtual void operator()() = 0;

    virtual ~ScrollBarFunction() {};
};

struct MoveTarget : ScrollBarFunction 
{
    Widget* target;

    MoveTarget(Widget* _target) :
    target (_target)
    {}

    void operator()()
    {
        fprintf(stderr, "Want to move\n");
        target->Move(-delta);

        target->UpdateRegionSet();
    }
};

class ScrollBar : public Widget
{
    bool             pressed;
    Vector           sensitivity;
    Color            background_color;
    RectangleWidget* slider;
    Vector           last_mouse_pos;

    ScrollBarFunction* scroll;

public:
    // slider_size specified as a fraction of the scrollbar size
    ScrollBar(Vector _position,  Vector _size, 
              Color _background, Color _slider_color,
              Vector _slider_size,
              ScrollBarFunction* _scroll = nullptr);

    ScrollBar(Vector _position,  Vector _size, 
              Color _background, Color _slider_color,
              Vector _slider_size,
              Widget* target, 
              Vector visible_box_offset, Vector visible_box_size);

    bool OnMouseRelease(MouseCondition mouse) override;
    bool OnMousePress  (MouseCondition mouse) override;
    bool OnMouseMove   (MouseCondition mouse) override;
    void Render        (RenderTarget* tr)     override;

    ~ScrollBar();
};

#endif // SYM_SCROLL_BAR