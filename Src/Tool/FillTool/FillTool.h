#ifndef SYM_FILL_TOOL
#define SYM_FILL_TOOL

#include "../Tool.h"

class FillTool : public Tool
{
public : 
    FillTool()
    {};

    void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse, plugin::Color color) override;
    void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse, plugin::Color color) override;
    void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse, plugin::Color color) override;
    void disable       (plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                        plugin::MouseContext mouse, plugin::Color         color) override;
};

#endif //SYM_FILL_TOOL