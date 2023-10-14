#include "Canvas.h"

#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

const Color kBackgroundColor = Color(50, 50, 50);

Canvas::Canvas(Vector _position, Vector _size, ToolManager* _tm) :
Widget(_position, _size),
tm (_tm),
data (RenderTarget(_size)),
tmp  (RenderTarget(_size))
{}

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
        render_target->DrawRect(position, size, reg_set, 
                                kBackgroundColor, 0, Color(0, 0, 0));  //border + background
        
        data.Display();
        render_target->DrawSprite(position, data.GetTexture(), reg_set);
        Widget::Render(render_target);
    }
}
