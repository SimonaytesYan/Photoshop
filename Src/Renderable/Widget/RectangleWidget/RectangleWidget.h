#ifndef SYM_RECT_WIDGET
#define SYM_RECT_WIDGET

#include "../Widget.h"

class RectangleWidget : public Widget
{
    RenderTarget  rt;

public:
    RectangleWidget(plugin::Vec2 position,    plugin::Vec2 size,
                    plugin::Color background, bool         available = true);

    RectangleWidget(plugin::Vec2 position, plugin::Vec2 size, 
                    bool available = true);

    void render(RenderTarget* render_target);

    RenderTarget* GetRT()
    { return &rt; }
};

#endif //SYM_RECT_WIDGET