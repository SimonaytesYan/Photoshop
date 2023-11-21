#ifndef SYM_SPLINE_TOOL
#define SYM_SPLINE_TOOL

#include "../Tool.h"
#include "../../List.h"

class SplineTool : public Tool
{
    List<plugin::Vec2> vertexes;
    double thickness = 10;
public : 
    SplineTool(double _thickness) :
    Tool     (),
    vertexes (List<plugin::Vec2>(0)),
    thickness(_thickness)
    {}

    void paintOnPress    (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                          MouseContext mouse, plugin::Color color) override;
    void paintOnMove     (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                          MouseContext mouse, plugin::Color color)
    {};

    void paintOnRelease  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                          MouseContext mouse, plugin::Color color)
    {};
    void disable         (plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                          MouseContext mouse, plugin::Color         color) override;
};

#endif //SYM_SPLINE_TOOL