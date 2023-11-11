#ifndef SYM_WINDOW
#define SYM_WINDOW

#include "../Widget.h"

class Window : public Widget
{
    Vector old_mouse_pos;
    bool   moving;

public:
    Window(Vector position, Vector size, const char* header);
    ~Window();

    void Render(RenderTarget* render_target)  override;
    bool InsideP(Vector v);
    bool OnMousePress(MouseCondition mouse)   override;
    bool OnMouseMove (MouseCondition mouse)   override;
    bool OnMouseRelease(MouseCondition mouse) override;
    
    void Close();
    void SetMoving(bool new_moving) { moving = new_moving; }
};

#endif //SYM_WINDOW