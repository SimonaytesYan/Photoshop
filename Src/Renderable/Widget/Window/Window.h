#ifndef SYM_WINDOW
#define SYM_WINDOW

#include "../Widget.h"

class Window : public Widget
{
    Vector old_mouse_pos;
    bool   moving;

public:
    Window(Vector position, Vector size, char* header);
    ~Window();

    void Render(RenderTarget* render_target)  override;
    bool InsideP(Vector v);
    bool OnMousePress(MouseCondition mouse)   override;
    bool OnMouseMove (MouseCondition mouse)   override;
    bool OnMouseRelease(MouseCondition mouse) override;
    void Close();

    friend void ButtonMove(void* args);
};

#endif //SYM_WINDOW