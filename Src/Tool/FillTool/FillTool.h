#ifndef SYM_FILL_TOOL
#define SYM_FILL_TOOL

#include "../Tool.h"

class FillTool : public Tool
{
public : 
    FillTool()
    {};

    void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void Disable       (RenderTarget&  data,  RenderTarget& tmp, 
                        MouseContext mouse, plugin::Color         color) override;
};

#endif //SYM_FILL_TOOL