#ifndef SYM_SPLINE_TOOL
#define SYM_SPLINE_TOOL

#include "../Tool.h"
#include "../../List.h"

class SplineTool : public Tool
{
    List<Vector> vertexes;
    double thickness = 10;
public : 
    SplineTool(double _thickness) :
    Tool     (),
    vertexes (List<Vector>(0)),
    thickness(_thickness)
    {}

    void PaintOnPress    (RenderTarget& data, RenderTarget& tmp, 
                          MouseCondition mouse, Color color) override;
    void PaintOnMove     (RenderTarget& data, RenderTarget& tmp, 
                          MouseCondition mouse, Color color)
    {};

    void PaintOnRelease  (RenderTarget& data, RenderTarget& tmp, 
                          MouseCondition mouse, Color color)
    {};
    void Disable         (RenderTarget&  data,  RenderTarget& tmp, 
                          MouseCondition mouse, Color         color) override;
};

#endif //SYM_SPLINE_TOOL