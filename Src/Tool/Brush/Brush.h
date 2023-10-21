#ifndef SYM_BRUSH
#define SYM_BRUSH

#include "../Tool.h"
#include "../../List.h"

class Brush : Tool
{
    double       thickness;
    bool         drawing;
    List<Vector> vertexes;

public : 
    Brush(double _thickness) :
    thickness(_thickness),
    drawing  (false),
    vertexes (List<Vector>(0))
    {}

    void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                        MouseCondition mouse, Color color) override;
    void Disable       () override;
    void Interpolation(RenderTarget& data, RenderTarget& tmp, Color color);
};

#endif //SYM_BRUSH