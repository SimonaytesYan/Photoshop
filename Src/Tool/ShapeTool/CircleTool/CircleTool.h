#ifndef SYM_CIRCLE_TOOL
#define SYM_CIRCLE_TOOL

#include "../ShapeTool.h"

class CircleTool : public ShapeTool
{
public : 
    CircleTool(double _thickness) :
    ShapeTool(_thickness)
    {}

    void CalcAndDrawShape(RenderTarget& target, 
                           MouseCondition mouse, 
                           Color color) override;
};

#endif //SYM_CIRCLE_TOOL