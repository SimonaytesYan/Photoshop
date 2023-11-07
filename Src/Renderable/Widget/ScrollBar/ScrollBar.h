#ifndef SYM_SCROLL_BAR
#define SYM_SCROLL_BAR

#include "../Widget.h"

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
        fprintf(stderr, "slider = %p\n", slider);
        AddObject(slider);
    }

    bool OnMouseRelease(MouseCondition mouse) override;
    bool OnMousePress  (MouseCondition mouse) override;
    bool OnMouseMove   (MouseCondition mouse) override;
    void Render        (RenderTarget* tr)     override;
};

#endif // SYM_SCROLL_BAR