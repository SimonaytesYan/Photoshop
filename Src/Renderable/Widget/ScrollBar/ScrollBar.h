#ifndef SYM_SCROLL_BAR
#define SYM_SCROLL_BAR

#include "../Widget.h"

class Interlayer : public Widget
{
public :
    Interlayer(Vec2 position, Vec2 size) :
    Widget(position, size)
    {
    }

    bool OnMousePress(MouseContext mouse)   override
    {
        if (InsideP(mouse.position))
            return Widget::OnMousePress(mouse);
        return false;
    }

};

struct ScrollBarFunction 
{
    Vec2 delta;
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
    Vec2           sensitivity;
    Color            background_color;
    RectangleWidget* slider;
    Vec2           last_mouse_pos;

    ScrollBarFunction* scroll;

public:
    // slider_size specified as a fraction of the scrollbar size
    ScrollBar(Vec2 _position,  Vec2 _size, 
              Color _background, Color _slider_color,
              Vec2 _slider_size,
              ScrollBarFunction* _scroll = nullptr);

    ScrollBar(Vec2 _position,  Vec2 _size, 
              Color _background, Color _slider_color,
              Vec2 _slider_size,
              Widget* target, 
              Vec2 visible_box_offset, Vec2 visible_box_size);

    bool OnMouseRelease(MouseContext mouse) override;
    bool OnMousePress  (MouseContext mouse) override;
    bool OnMouseMove   (MouseContext mouse) override;
    void Render        (RenderTarget* tr)     override;

    ~ScrollBar();
};

#endif // SYM_SCROLL_BAR