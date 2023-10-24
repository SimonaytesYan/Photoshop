#ifndef SYM_POLYLINE_TOOL
#define SYM_POLYLINE_TOOL

#include "../Tool.h"
#include "../../DynArray.h"

class PolylineTool : public Tool
{
    DynArray<Vector> vertexes;

public : 
    PolylineTool() :
    vertexes(DynArray<Vector>(0))
    {}
    
    void CalcAndDrawPolyline(RenderTarget& target, 
                          MouseCondition mouse, Color color);
    void PaintOnPress    (RenderTarget& data, RenderTarget& tmp, 
                          MouseCondition mouse, Color color) override;
    void PaintOnMove     (RenderTarget& data, RenderTarget& tmp, 
                          MouseCondition mouse, Color color) override;
    void PaintOnRelease  (RenderTarget& data, RenderTarget& tmp, 
                          MouseCondition mouse, Color color) override
    {}
    void Disable         (RenderTarget&  data,  RenderTarget& tmp, 
                          MouseCondition mouse, Color         color) override;
};

#endif //SYM_POLYLINE_TOOL