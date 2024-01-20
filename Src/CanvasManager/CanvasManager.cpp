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

void CanvasManager::RecreateWindowMenu()
{
    for (int i = window_menu->getSubWidgets().Begin(); i != -1; )
    {
        fprintf(stderr, "recreate window i = %d\n", i);
        if (window_menu->getMainButton() != window_menu->getSubWidgets()[i].val) // Skip button that opens menu
        {
            fprintf(stderr, "recreate window delete i = %d\n", i);
            delete window_menu->getSubWidgets()[i].val;
        }

        int next = window_menu->getSubWidgets().Iterate(i);
        window_menu->getSubWidgets().Remove(i);
        i = next;
    }

    for (int i = canvases.Begin(); i != -1; i = canvases.Iterate(i))
    {
        ToForegroundCanvasWindow* functor = new ToForegroundCanvasWindow(canvases[i].val, 
                                                                         this, 
                                                                         event_manager);
        TextButton* text_button = new TextButton(plugin::Vec2(0, 0), plugin::Vec2(200, 50), 
                                                 kButtonColor, 
                                                 font, 20, canvases[i].val->getName(), plugin::Color(255, 255, 255), 
                                                 functor);
        window_menu->registerSubWidget(text_button);
    }
}

void CanvasManager::unregisterCanvas(Canvas* canvas)
{
    fprintf(stderr, "We want close canvas %s\n", canvas->getName());
    for (int i = canvases.Begin(); i != -1; i = canvases.Iterate(i))
    {
        if (canvases[i].val == canvas)
        {
            fprintf(stderr, "Close canvas %s\n", canvases[i].val->getName());
            canvases.Remove(i);

            RecreateWindowMenu();
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
