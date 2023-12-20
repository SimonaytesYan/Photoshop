#ifndef SYM_CANVAS
#define SYM_CANVAS

#include "../Widget.h"
#include "../../../ToolManager/ToolManager.h" 
#include "../../../FilterManager/FilterManager.h"
#include "../../../Standart/Standart.h"
#include "../../../CanvasManager/CanvasManager.h"

const plugin::Color kCanvasBackgroundColor = plugin::Color(50, 50, 50);

class Canvas : public Widget
{
    bool           drawing;
    ToolManager*   tm;
    FilterManager* fm;
    RenderTarget   data;
    RenderTarget   tmp;
    char*          name;
    CanvasManager* canvas_manager;
    
    void disableTool(plugin::MouseContext mouse);

public :
    Canvas(plugin::Vec2 position, plugin::Vec2 size, 
           ToolManager* tm, FilterManager* fm, 
           const char* name, CanvasManager* canvas_manager);

    ~Canvas()
    {
        delete name;
        canvas_manager->unregisterCanvas(this);
    };

    RenderTarget* GetData() { return &data; }

    const char* getName() { return name; }

    bool onMousePress  (plugin::MouseContext mouse)        override;
    bool onMouseRelease(plugin::MouseContext mouse)        override;
    bool onMouseMove   (plugin::MouseContext mouse)        override;
    void render        (RenderTarget* render_target) override;
    void Clear();
};

#endif //SYM_CANVAS