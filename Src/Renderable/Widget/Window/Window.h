#ifndef SYM_WINDOW
#define SYM_WINDOW

#include "../Widget.h"

class Window : public Widget
{
    plugin::Vec2 old_mouse_pos;
    bool   moving;

public:
    Window(plugin::Vec2 position, plugin::Vec2 size, const char* header);
    ~Window();

    void render(RenderTarget* render_target)  override;
    bool InsideP(plugin::Vec2 v);
    bool onMousePress(plugin::MouseContext mouse)   override;
    bool onMouseMove (plugin::MouseContext mouse)   override;
    bool onMouseRelease(plugin::MouseContext mouse) override;
    
    void addIntoWindow(Widget* new_widget);
    void Close();
    void SetMoving(bool new_moving) { moving = new_moving; }
};

#endif //SYM_WINDOW