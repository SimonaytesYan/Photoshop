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
    
    void CalcAndDrawPolyline(RenderTarget& target, 
                          MouseContext mouse, plugin::Color color);
    void paintOnPress    (plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                          MouseContext mouse, plugin::Color color) override;
    void paintOnMove     (plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                          MouseContext mouse, plugin::Color color) override;
    void paintOnRelease  (plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                          MouseContext mouse, plugin::Color color) override
    {}
    void disable         (RenderTarget&  data,  plugin::RenderTargetI* tmp, 
                          MouseContext mouse, plugin::Color         color) override;
};

#endif //SYM_POLYLINE_TOOL