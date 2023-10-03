#ifndef SYM_WINDOW
#define SYM_WINDOW

#include "../Widget.h"

class Window : public Widget
{
    Vector size;

public:
    Window(Vector position, Vector size, char* header);
    ~Window();

    void Render  (RenderTarget* render_target) override;
    bool Inside_p(Vector v);
    bool OnMousePress(MouseCondition mouse) override;
    void Close();
};

#endif //SYM_WINDOW