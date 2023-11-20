#include "Canvas.h"

#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

Canvas::Canvas(plugin::Vec2 _position, plugin::Vec2 _size, 
               ToolManager* _tm, FilterManager* _fm) :
Widget(_position, _size),
tm   (_tm),
fm   (_fm),
data (RenderTarget(_size)),
tmp  (RenderTarget(_size))
{
    data.clear(kCanvasBackgroundColor);
    tmp.clear(plugin::Color(0, 0, 0, 0));
}

void Canvas::DisableTool(MouseContext mouse)
{
    if (tm != nullptr && drawing)
    {
        mouse.position = mouse.position - position;
        tm->DisableTool(data, tmp, mouse);
        drawing = false;
    }
}

bool Canvas::onMousePress(MouseContext mouse)
{
    if (Widget::onMousePress(mouse))
        return true;

    if (InsideP(mouse.position))
    {
        drawing = true;
        mouse.position = mouse.position - position;
        
        if (fm != nullptr && fm->GetActive())
        {
            fm->SetRenderTarget(&data);
            fm->ApplyLastFilter();
        }
        else if (tm != nullptr)
            tm->PaintOnPress(data, tmp, mouse);
        return true;
    }
    
    return false;
}

bool Canvas::onMouseMove(MouseContext mouse)
{
    if (Widget::onMouseMove(mouse))
        return true;
        
    static int cnt = 0;
    if (!InsideP(mouse.position))
    {
        DisableTool(mouse);
        drawing = false;
        return false;
    }

    if (drawing == false)
    {
        //DisableTool(mouse);
        //drawing = true;
        return false;
    }

    mouse.position = mouse.position - position;
    tm->PaintOnMove(data, tmp, mouse);
    return true;
}

bool Canvas::onMouseRelease(MouseContext mouse)
{
    if (Widget::onMouseRelease(mouse))
    {
        DisableTool(mouse);
        return true;
    }

    if (available && InsideP(mouse.position))
    {
        if (tm != nullptr)
        {
            mouse.position = mouse.position - position;
            tm->PaintOnRelease(data, tmp, mouse);    
        }
    }

    return false;
}

void Canvas::Render(RenderTarget* render_target)
{
    if (available)
    {
        data.display();
        render_target->DrawSprite(position, data.GetTexture(), reg_set);
        tmp.display();
        render_target->DrawSprite(position, tmp.GetTexture(), reg_set);
        Widget::Render(render_target);
    }
}

void Canvas::Clear()
{
    data.clear(kCanvasBackgroundColor);
    tmp.clear(plugin::Color(0, 0, 0, 0));
}
