#ifndef SYM_BRUSH
#define SYM_BRUSH

#include "../Tool.h"
#include "../../List.h"

class Brush : public Tool
{
    double       thickness;
    bool         drawing;
    List<Vec2> vertexes;

public : 
    Brush(double _thickness) :
    thickness(_thickness),
    drawing  (false),
    vertexes (List<Vec2>(0))
    {}

    void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, Color color) override;
    void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, Color color) override;
    void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseContext mouse, Color color) override;
    void Disable       (RenderTarget&  data,  RenderTarget& tmp, 
                        MouseContext mouse, Color         color) override;
    void Interpolation(RenderTarget& data, RenderTarget& tmp, Color color);
};

#endif //SYM_BRUSH