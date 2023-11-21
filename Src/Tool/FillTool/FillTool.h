#ifndef SYM_FILL_TOOL
#define SYM_FILL_TOOL

#include "../Tool.h"

class FillTool : public Tool
{
public : 
    FillTool()
    {};

    void paintOnRelease(plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void paintOnMove   (plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void paintOnPress  (plugin::RendertTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void disable       (RenderTarget&  data,  plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color         color) override;
};

#endif //SYM_FILL_TOOL