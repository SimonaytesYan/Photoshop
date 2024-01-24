#include "CanvasManager.h"
#include "../Renderable/Widget/Canvas/Canvas.h"
#include "../ClipRegion/ClipRegion.h"
#include "../RegionSet/RegionSet.h"

void CanvasManager::registerCanvas(Canvas* canvas)
{
    canvases.PushBack(canvas);

    ToForegroundCanvasWindow* functor = new ToForegroundCanvasWindow(canvas, this, event_manager);

    RecreateWindowMenu();
    active_canvas = canvas;
}

// Run this function every time, when list of canvases changed 
void CanvasManager::RecreateWindowMenu()
{
    fprintf(stderr, "window_menu->getSubWidgets().size = %d\n", window_menu->getSubWidgets().size);

    // Delete all buttons from menu except main button  

    Widget* main_button = window_menu->getMainButton();     // Save main_button
    window_menu->unregisterSubWidget(main_button);

    for (int i = window_menu->getSubWidgets().Begin(); i != -1; i = window_menu->getSubWidgets().Iterate(i))
        delete window_menu->getSubWidgets()[i].val;
    window_menu->getSubWidgets().Clear();

    window_menu->registerSubWidget(main_button);        // Recover main_button

    // Create buttons
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

            fprintf(stderr, "canvases.size = %d\n", canvases.size);

            RecreateWindowMenu();
            break;
        }
    }

    if (active_canvas == canvas)
    {
        if (canvases.Begin() == -1)
            active_canvas = nullptr;
        else
            active_canvas = canvases[canvases.Begin()].val;
    }
}

// We believe that all canvases are inside windows, that are children of root 
void ToForegroundCanvasWindow::operator()()
{
    Widget* canvas_window = canvas->getWidgetParent();

    if (canvas_window->getWidgetParent() != nullptr)
    {
        fprintf(stderr, "Put canvas_window to foreground\n");
        canvas_window->getWidgetParent()->ToForeground(canvas_window);
    }
    else
    {
        canvas_window->getWidgetParent()->ToForeground(canvas_window);
        event_manager->onMousePress(plugin::MouseContext(canvas->getPos(), plugin::MouseButton::Unknown));
    }

    canvas_manager->setActiveCanvas(canvas);
}
