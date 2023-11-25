#ifndef SYM_SCROLL_BAR
#define SYM_SCROLL_BAR

#include "../Widget.h"
#include "../RectangleWidget/RectangleWidget.h"

class Interlayer : public Widget
{
public :
    Interlayer(plugin::Vec2 position, plugin::Vec2 size) :
    Widget(position, size)
    {
    }

    bool onMousePress(plugin::MouseContext mouse)   override
    {
        if (InsideP(mouse.position))
            return Widget::onMousePress(mouse);
        return false;
    }

};

struct ScrollBarFunction 
{
    plugin::Vec2 delta;
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
        target->move(-delta);

        target->UpdateRegionSet();
    }
};

class ScrollBar : public Widget
{
    bool             pressed;
    plugin::Vec2           sensitivity;
    plugin::Color            background_color;
    RectangleWidget* slider;
    plugin::Vec2           last_mouse_pos;

    ScrollBarFunction* scroll;

public:
    // slider_size specified as a fraction of the scrollbar size
    ScrollBar(plugin::Vec2 _position,  plugin::Vec2 _size, 
              plugin::Color _background, plugin::Color _slider_color,
              plugin::Vec2 _slider_size,
              ScrollBarFunction* _scroll = nullptr);

    ScrollBar(plugin::Vec2 _position,  plugin::Vec2 _size, 
              plugin::Color _background, plugin::Color _slider_color,
              plugin::Vec2 _slider_size,
              Widget* target, 
              plugin::Vec2 visible_box_offset, plugin::Vec2 visible_box_size);

    bool onMouseRelease(plugin::MouseContext mouse) override;
    bool onMousePress  (plugin::MouseContext mouse) override;
    bool onMouseMove   (plugin::MouseContext mouse) override;
    void render        (RenderTarget* tr)     override;

    ~ScrollBar();
};

#endif // SYM_SCROLL_BAR