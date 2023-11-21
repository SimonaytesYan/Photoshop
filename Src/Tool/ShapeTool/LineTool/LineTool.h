#ifndef SYM_LINE_TOOL
#define SYM_LINE_TOOL

#include "../ShapeTool.h"

class LineTool : public ShapeTool
{
public : 
    LineTool() :
    ShapeTool(0)
    {}
    
    void CalcAndDrawShape(RenderTarget* target, 
                          MouseContext mouse, 
                          plugin::Color color) override;
};

#endif //SYM_LINE_TOOL