#include "Canvas.h"

#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

Canvas::Canvas(Vector _position, Vector _size, ToolManager* _tm) :
Widget(_position, _size),
tm (_tm),
data (RenderTarget(_size)),
tmp  (RenderTarget(_size))
{
    data.Clear(kCanvasBackgroundColor);
    tmp.Clear(Color(0, 0, 0, 0));
}

bool Canvas::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position) && tm != nullptr)
    {
        mouse.position = mouse.position - position;
        tm->PaintOnPress(data, tmp, mouse);
        return true;
    }

    return false;
}

bool Canvas::OnMouseMove(MouseCondition mouse)
{
    if (!InsideP(mouse.position))
    {
        if (tm != nullptr)
        {
            mouse.position = mouse.position - position;
            tm->PaintOnRelease(data, tmp, mouse);
        }
    }
    else
    {
        mouse.position = mouse.position - position;
        tm->PaintOnMove(data, tmp, mouse);
    }

    return false;
}

bool Canvas::OnMouseRelease(MouseCondition mouse)
{
    if (Widget::OnMouseRelease(mouse))
        return true;
    if (available && InsideP(mouse.position))
    {

        if (tm != nullptr)
        {
            mouse.position = mouse.position - position;
            tm->PaintOnRelease(data, tmp, mouse);    
        }
        
        return true;
    }
    return false;
}

void Canvas::Render(RenderTarget* render_target)
{
    if (available)
    {
        data.Display();
        render_target->DrawSprite(position, data.GetTexture(), reg_set);
        tmp.Display();
        render_target->DrawSprite(position, tmp.GetTexture(), reg_set);
        Widget::Render(render_target);
    }
}

void Canvas::Clear()
{
    data.Clear(kCanvasBackgroundColor);
    tmp.Clear(Color(0, 0, 0, 0));
}
