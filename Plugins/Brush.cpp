#include "Brush.h"
#include "CutMullRom/CutMullRom.h"

extern "C" plugin::Plugin* getInstance(plugin::App *app)
{
    return new BrushPlugin(app);
}

BrushPlugin::BrushPlugin(plugin::App* app) :
app (app)
{ 
    tool = new BrushTool(10);

    name = "Super brush";
    type = plugin::InterfaceType::Tool;
}

plugin::Array<const char*> BrushTool::getParamNames()
{ 
    return {0, nullptr}; 
}

plugin::Array<double> BrushTool::getParams()
{ 
    return {0, nullptr}; 
}

void BrushTool::setParams(plugin::Array<double> params)
{ }

void BrushTool::paintOnPress(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                             plugin::MouseContext mouse, plugin::Color color)
{
    drawing = true;

    vertexes.PushBack(mouse.position);
    DrawUsingCatMullRom_plugin(data, tmp, color, thickness, vertexes);
}

void BrushTool::paintOnMove(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                            plugin::MouseContext mouse, plugin::Color color)
{
    if (drawing)
    {
        if (vertexes.size != 0 && vertexes[vertexes.End()].val == mouse.position)
            return;
        vertexes.PushBack(mouse.position);
        if (vertexes.size >= 5)
            vertexes.PopFront();
        
        DrawUsingCatMullRom_plugin(data, tmp, color, thickness, vertexes);
    }   
}

void BrushTool::paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                               plugin::MouseContext mouse, plugin::Color color)
{
    DrawTmpToData_plugin(data, tmp, color, thickness, vertexes);

    drawing   = false;
    vertexes.Clear();
}

void BrushTool::disable(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse, plugin::Color color)
{ 
    if (drawing)
    {
        DrawTmpToData_plugin(data, tmp, color, thickness, vertexes);

        drawing   = false;
        vertexes.Clear();
    }
}