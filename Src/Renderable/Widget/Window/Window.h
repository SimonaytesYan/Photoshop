#ifndef SYM_WINDOW
#define SYM_WINDOW

#include "../Widget.h"

class Window : public Widget
{
    Vec2 old_mouse_pos;
    bool   moving;

public:
    Window(Vec2 position, Vec2 size, const char* header);
    ~Window();

    void Render(RenderTarget* render_target)  override;
    bool InsideP(Vec2 v);
    bool OnMousePress(MouseContext mouse)   override;
    bool OnMouseMove (MouseContext mouse)   override;
    bool OnMouseRelease(MouseContext mouse) override;
    
    void Close();
    void SetMoving(bool new_moving) { moving = new_moving; }
};

#endif //SYM_WINDOW