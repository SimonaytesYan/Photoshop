#ifndef SYM_BRUSH
#define SYM_BRUSH

#include "../Tool.h"
#include "../../List.h"

class Brush : public Tool
{
    double       thickness;
    bool         drawing;
    List<plugin::Vec2> vertexes;

public : 
    Brush(double _thickness) :
    thickness(_thickness),
    drawing  (false),
    vertexes (List<plugin::Vec2>(0))
    {}

    void paintOnPress  (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void paintOnMove   (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void disable       (plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                        MouseContext mouse, plugin::Color         color) override;
    void Interpolation(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::Color color);
};

#endif //SYM_BRUSH