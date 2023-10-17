#ifndef SYM_LINE_TOOL
#define SYM_LINE_TOOL

#include "../ShapeTool.h"

class LineTool : public ShapeTool
{
public : 
    LineTool(double _thickness) :
    ShapeTool(_thickness)
    {}
    
    void CalcAndDrawShape(RenderTarget& target, 
                          MouseCondition mouse, 
                          Color color) override;
};

#endif //SYM_LINE_TOOL