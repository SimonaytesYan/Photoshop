#ifndef SYM_CANVAS
#define SYM_CANVAS

#include "../Widget.h"
#include "../../../ToolManager/ToolManager.h" 

const Color kCanvasBackgroundColor = Color(50, 50, 50);

class Canvas : public Widget
{
    bool         drawing;
    ToolManager* tm;
    RenderTarget data;
    RenderTarget tmp;

public :
    Canvas(Vector position, Vector size, ToolManager* tm = nullptr);

    ~Canvas()
    {};

    bool OnMousePress  (MouseCondition mouse)        override;
    bool OnMouseRelease(MouseCondition mouse)        override;
    bool OnMouseMove   (MouseCondition mouse)        override;
    void Render        (RenderTarget* render_target) override;
    void Clear();
};

#endif //SYM_CANVAS