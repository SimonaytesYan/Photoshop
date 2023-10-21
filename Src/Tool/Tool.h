#ifndef SYM_TOOL
#define SYM_TOOL

#include "../Vector/Vector.h"
#include "../Color.h"
#include "../Keys.h"

class RenderTarget;

class Tool
{
    
protected :
    Vector start_pos;
    Vector last_pos;
    bool   drawing;

public :
    Tool() :
    start_pos (Vector(-1, -1)),
    last_pos  (Vector(-1, -1)),
    drawing   (false)
    {};

    virtual void PaintOnPress  (RenderTarget& data, RenderTarget& tmp, 
                                MouseCondition mouse, Color color) = 0;
    virtual void PaintOnMove   (RenderTarget& data, RenderTarget& tmp, 
                                MouseCondition mouse, Color color) = 0;
    virtual void PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                                MouseCondition mouse, Color color) = 0;
    virtual void Disable       () = 0;
};

#endif //SYM_TOOL