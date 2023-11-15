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
    
    void DisableTool(MouseContext mouse);

public :
    Canvas(Vec2 position, Vec2 size, 
           ToolManager* tm = nullptr, FilterManager* fm = nullptr);

    ~Canvas()
    {};

    RenderTarget* GetData() { return &data; }

    bool onMousePress  (MouseContext mouse)        override;
    bool onMouseRelease(MouseContext mouse)        override;
    bool onMouseMove   (MouseContext mouse)        override;
    void Render        (RenderTarget* render_target) override;
    void Clear();
};

#endif //SYM_CANVAS