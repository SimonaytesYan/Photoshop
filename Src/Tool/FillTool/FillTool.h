#ifndef SYM_FILL_TOOL
#define SYM_FILL_TOOL

#include "../Tool.h"

class FillTool : Tool
{
public : 
    FillTool()
    {};

    void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void Disable       () override;
};

#endif //SYM_FILL_TOOL