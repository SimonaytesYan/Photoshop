#ifndef SYM_CIRCLE_TOOL
#define SYM_CIRCLE_TOOL

#include "../Tool.h"

class CircleTool : Tool
{
    bool   drawing;
    double thickness;

public : 
    CircleTool(double _thickness) :
    drawing   (false),
    thickness (_thickness)
    {}

    void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void Disable       () override;

    void CulcAndDrawCircle(RenderTarget& target, MouseCondition mouse, Color color);
};

#endif //SYM_CIRCLE_TOOL