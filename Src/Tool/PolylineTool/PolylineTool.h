#ifndef SYM_POLYLINE_TOOL
#define SYM_POLYLINE_TOOL

#include "../Tool.h"
#include "../../DynArray.h"

class PolylineTool : public Tool
{
    DynArray<Vec2> vertexes;

public : 
    PolylineTool() :
    vertexes(DynArray<Vec2>(0))
    {}
    
    void CalcAndDrawPolyline(RenderTarget& target, 
                          MouseContext mouse, Color color);
    void PaintOnPress    (RenderTarget& data, RenderTarget& tmp, 
                          MouseContext mouse, Color color) override;
    void PaintOnMove     (RenderTarget& data, RenderTarget& tmp, 
                          MouseContext mouse, Color color) override;
    void PaintOnRelease  (RenderTarget& data, RenderTarget& tmp, 
                          MouseContext mouse, Color color) override
    {}
    void Disable         (RenderTarget&  data,  RenderTarget& tmp, 
                          MouseContext mouse, Color         color) override;
};

#endif //SYM_POLYLINE_TOOL