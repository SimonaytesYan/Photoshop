#ifndef SYM_CANVAS
#define SYM_CANVAS

#include "../Widget.h"
#include "../../../ToolManager/ToolManager.h" 
#include "../../../FilterManager/FilterManager.h"

const Color kCanvasBackgroundColor = Color(50, 50, 50);

class Canvas : public Widget
{
    bool           drawing;
    ToolManager*   tm;
    FilterManager* fm;
    RenderTarget   data;
    RenderTarget   tmp;
    
    void DisableTool(MouseCondition mouse);

public :
    Canvas(Vector position, Vector size, 
           ToolManager* tm = nullptr, FilterManager* fm = nullptr);

    ~Canvas()
    {};

    bool OnMousePress  (MouseCondition mouse)        override;
    bool OnMouseRelease(MouseCondition mouse)        override;
    bool OnMouseMove   (MouseCondition mouse)        override;
    void Render        (RenderTarget* render_target) override;
    void Clear();
};

#endif //SYM_CANVAS