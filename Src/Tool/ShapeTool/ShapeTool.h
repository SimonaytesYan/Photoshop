#ifndef SYM_SHAPE_TOOL
#define SYM_SHAPE_TOOL

#include "../Tool.h"

class ShapeTool : public Tool
{
protected:
    bool   drawing;
    double thickness;

public : 
    ShapeTool(double _thickness) :
    drawing   (false),
    thickness (_thickness)
    {}

    virtual void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                                MouseContext mouse, plugin::Color color) override;
    virtual void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                                MouseContext mouse, plugin::Color color) override;
    virtual void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                                MouseContext mouse, plugin::Color color) override;
    virtual void Disable       (RenderTarget&  data,  RenderTarget& tmp, 
                                MouseContext mouse, plugin::Color         color) override;

    virtual void CalcAndDrawShape(RenderTarget& target, 
                                  MouseContext mouse, 
                                  plugin::Color color) = 0;
};

#endif //SYM_SHAPE_TOOL