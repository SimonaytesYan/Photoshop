#ifndef SYM_CANVAS_MANAGER
#define SYM_CANVAS_MANAGER

#include "../List.h"
#include "../Renderable/Widget/Menu/VerticalMenu/VerticalMenu.h"
#include "../Constants.h"

class Canvas;
class CanvasManager;

struct ToForegroundCanvasWindow : ButtonFunction
{
    CanvasManager* canvas_manager;
    Canvas* canvas;
    EventManager* event_manager;

    ToForegroundCanvasWindow(Canvas* canvas, CanvasManager* canvas_manager, 
                             EventManager* event_manager) :
    canvas_manager(canvas_manager),
    canvas        (canvas),
    event_manager (event_manager)
    { }

    void operator()() override;
};

class CanvasManager
{
    List<Canvas*> canvases;
    VerticalMenu* window_menu;
    Font          font;
    EventManager* event_manager;

    Canvas* active_canvas;

public :

    CanvasManager(VerticalMenu* window_menu, EventManager* event_manager) :
    canvases      (List<Canvas*>(0)),
    event_manager (event_manager)
    {
        active_canvas = nullptr;
        font.LoadFont(kFontFile);
    }


    void registerCanvas  (Canvas* canvas);
    void unregisterCanvas(Canvas* canvas);
    void RecreateWindowMenu();

    Canvas* GetActiveCanvas()
    { return active_canvas; }

    void setActiveCanvas(Canvas* canvas)
    { active_canvas = canvas; }

    void SetWindowMenu(VerticalMenu* menu)
    { window_menu = menu; }
};

#endif