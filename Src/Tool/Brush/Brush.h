#ifndef SYM_BRUSH
#define SYM_BRUSH

#include "../Tool.h"

class Brush : Tool
{
    double r;
    bool drawing;

public : 
    Brush(double _r) :
    r       (_r),
    drawing (false)
    {}

    void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void Disable       () override;
};

#endif //SYM_BRUSH