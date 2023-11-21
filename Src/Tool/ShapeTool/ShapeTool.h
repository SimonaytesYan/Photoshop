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

    virtual void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color) override;
    virtual void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color) override;
    virtual void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color color) override;
    virtual void disable       (RenderTarget&  data,  plugin::RenderTargetI* tmp, 
                                MouseContext mouse, plugin::Color         color) override;

    virtual void CalcAndDrawShape(RenderTarget& target, 
                                  MouseContext mouse, 
                                  plugin::Color color) = 0;
};

#endif //SYM_SHAPE_TOOL