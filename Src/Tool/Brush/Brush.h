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

    void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, plugin::Color color) override;
    void Disable       (RenderTarget&  data,  RenderTarget& tmp, 
                        MouseContext mouse, plugin::Color         color) override;
    void Interpolation(RenderTarget& data, RenderTarget& tmp, plugin::Color color);
};

#endif //SYM_BRUSH