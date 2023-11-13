#ifndef SYM_RECT_TOOL
#define SYM_RECT_TOOL

#include "../ShapeTool.h"

class RectTool : public ShapeTool
{
public : 
    RectTool(double _thickness) :
    ShapeTool(_thickness)
    {}
    
    void CalcAndDrawShape(RenderTarget& target, 
                           MouseContext mouse, 
                           Color color) override;
};

#endif //SYM_RECT_TOOL