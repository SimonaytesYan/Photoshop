#ifndef SYM_POLYLINE_TOOL
#define SYM_POLYLINE_TOOL

#include "../Tool.h"
#include "../../DynArray.h"

class PolylineTool : public Tool
{
    DynArray<plugin::Vec2> vertexes;

public : 
    PolylineTool() :
    vertexes(DynArray<plugin::Vec2>(0))
    {}
    
    void CalcAndDrawPolyline(plugin::RenderTargetI* target, 
                             plugin::MouseContext mouse, plugin::Color color);
    void paintOnPress    (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                          plugin::MouseContext mouse, plugin::Color color) override;
    void paintOnMove     (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                          plugin::MouseContext mouse, plugin::Color color) override;
    void paintOnRelease  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                          plugin::MouseContext mouse, plugin::Color color) override
    {}
    void disable         (plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                          plugin::MouseContext mouse, plugin::Color         color) override;
};

#endif //SYM_POLYLINE_TOOL