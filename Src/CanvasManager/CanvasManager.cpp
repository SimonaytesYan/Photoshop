#include "CanvasManager.h"
#include "../Renderable/Widget/Canvas/Canvas.h"
#include "../ClipRegion/ClipRegion.h"
#include "../RegionSet/RegionSet.h"

void CanvasManager::registerCanvas(Canvas* canvas)
{
    canvases.PushBack(canvas);

    ToForegroundCanvasWindow* functor = new ToForegroundCanvasWindow(canvas, this, event_manager);

    fprintf(stderr, "canvas->getName() = %s\n", canvas->getName());

    window_menu->registerSubWidget(new TextButton(plugin::Vec2(0, 0), plugin::Vec2(200, 50), 
                                                  kButtonColor, 
                                                  font, 20, canvas->getName(), plugin::Color(255, 255, 255), 
                                                  functor));

    active_canvas = canvas;
}

void CanvasManager::unregisterCanvas(Canvas* canvas)
{
    List<Widget*>& canvases_button = window_menu->getSubWidgets();

    for (int i = canvases.Begin(); i != -1; i = canvases.Iterate(i))
    {
        if (canvases[i].val == canvas)
        {
            canvases.Remove(i);
            canvases_button.Remove(i);
            break;
        }
    }

    if (active_canvas == canvas)
        active_canvas = canvases[canvases.Begin()].val;
}

void ToForegroundCanvasWindow::operator()()
{
    Widget* canvas_parent = canvas->getWidgetParent();
    
    canvas_parent->getWidgetParent()->ToForeground(canvas_parent);
    event_manager->onMousePress(plugin::MouseContext(canvas->getPos(), plugin::MouseButton::Unknown));

    canvas_manager->setActiveCanvas(canvas);
} 