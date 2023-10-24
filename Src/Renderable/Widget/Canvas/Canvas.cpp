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

void Canvas::DisableTool(MouseCondition mouse)
{
    if (tm != nullptr && drawing)
    {
        mouse.position = mouse.position - position;
        tm->DisableTool(data, tmp, mouse);
        drawing = false;
    }
}

bool Canvas::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position) && tm != nullptr)
    {
        drawing = true;
        mouse.position = mouse.position - position;
        tm->PaintOnPress(data, tmp, mouse);
        return true;
    }
    if (tm != nullptr && drawing)
        DisableTool(mouse);

    return false;
}

bool Canvas::OnMouseMove(MouseCondition mouse)
{
    static int cnt = 0;
    printf("Want draw %d\n", cnt++);   
    if (!InsideP(mouse.position))
    {
        if (tm != nullptr && drawing)
            DisableTool(mouse);
        return false;
    }

    if (drawing == false)
    {
        DisableTool(mouse);
        drawing = true;
    }
    
    printf("Go to draw %d\n", cnt++);   
    mouse.position = mouse.position - position;
    tm->PaintOnMove(data, tmp, mouse);
    return true;
}

bool Canvas::OnMouseRelease(MouseCondition mouse)
{
    if (Widget::OnMouseRelease(mouse))
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
