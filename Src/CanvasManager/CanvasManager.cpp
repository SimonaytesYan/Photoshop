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
    // Delete all buttons from menu except main button  

    Widget* main_button = window_menu->getMainButton();     // Save main_button
    window_menu->unregisterSubWidget(main_button);

    for (int i = window_menu->getSubWidgets().Begin(); i != -1; i = window_menu->getSubWidgets().Iterate(i))
        delete window_menu->getSubWidgets()[i].val;
    window_menu->getSubWidgets().Clear();

    window_menu->registerSubWidget(main_button);        // Recover main_button

    // Create buttons
    if (canvases.size < 1)
        return;
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
    for (int i = canvases.Begin(); i != -1; i = canvases.Iterate(i))
    {
        if (canvases[i].val == canvas)
        {
            canvases.Remove(i);
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

void PutAllParentsToForeground(Widget* widget)
{
    if (widget->getParent() == nullptr)
        return;
    
    widget->getWidgetParent()->ToForeground(widget);
    PutAllParentsToForeground(widget->getWidgetParent());
}

// We believe that all canvases are inside windows, that are children of root 
void ToForegroundCanvasWindow::operator()()
{
    PutAllParentsToForeground(canvas);
    canvas_manager->setActiveCanvas(canvas);
}
