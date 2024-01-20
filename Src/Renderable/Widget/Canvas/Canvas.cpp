#include "Canvas.h"

#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

Canvas::Canvas(plugin::Vec2 _position, plugin::Vec2 _size, 
               ToolManager* _tm, FilterManager* _fm, 
               const char* _name, CanvasManager* canvas_manager) :
Widget(_position, _size),
tm             (_tm),
fm             (_fm),
data           (RenderTarget(_size)),
tmp            (RenderTarget(_size)),
canvas_manager (canvas_manager)
{
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);

    canvas_manager->registerCanvas(this);

    drawing = false;
    data.clear(kCanvasBackgroundColor);
    tmp.clear(plugin::Color(0, 0, 0, 0));
}

void Canvas::disableTool(plugin::MouseContext mouse)
{
    if (tm != nullptr && drawing)
    {
        mouse.position = mouse.position - position;
        tm->disableTool((plugin::RenderTargetI*)&data, 
                        (plugin::RenderTargetI*)&tmp, 
                        mouse);
        drawing = false;
    }
}

bool Canvas::onMousePress(plugin::MouseContext mouse)
{
    if (Widget::onMousePress(mouse))
        return true;

    if (InsideP(mouse.position))
    {
        drawing = true;
        mouse.position = mouse.position - position;
        
        if (fm != nullptr && fm->GetActive())
        {
            fm->setRenderTarget((plugin::RenderTargetI*)&data);
            fm->applyFilter();
        }
        else if (tm != nullptr)
        {
            tm->paintOnPress((plugin::RenderTargetI*)&data, 
                             (plugin::RenderTargetI*)&tmp, 
                             mouse);
        }
        return true;
    }
    
    return false;
}

bool Canvas::onMouseMove(plugin::MouseContext mouse)
{
    if (Widget::onMouseMove(mouse))
        return true;
        
    static int cnt = 0;
    if (!InsideP(mouse.position))
    {
        disableTool(mouse);
        drawing = false;
        return false;
    }

    if (drawing == false)
    {
        //disableTool(mouse);
        //drawing = true;
        return false;
    }

    mouse.position = mouse.position - position;
    tm->paintOnMove((plugin::RenderTargetI*)&data, 
                    (plugin::RenderTargetI*)&tmp, 
                    mouse);
    return true;
}

bool Canvas::onMouseRelease(plugin::MouseContext mouse)
{
    if (Widget::onMouseRelease(mouse))
    {
        disableTool(mouse);
        return true;
    }

    if (available && InsideP(mouse.position) && visible)
    {
        if (tm != nullptr)
        {
            mouse.position = mouse.position - position;
            tm->paintOnRelease((plugin::RenderTargetI*)&data, 
                               (plugin::RenderTargetI*)&tmp, 
                               mouse);    
        }
    }

    return false;
}

void Canvas::render(RenderTarget* render_target)
{
    if (available && visible)
    {
        data.display();
        render_target->DrawSprite(position, data.GetTexture(), reg_set);
        tmp.display();
        render_target->DrawSprite(position, tmp.GetTexture(), reg_set);
        Widget::render(render_target);
    }
}

void Canvas::Clear()
{
    data.clear(kCanvasBackgroundColor);
    tmp.clear(plugin::Color(0, 0, 0, 0));
}
