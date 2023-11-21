#ifndef SYM_TOOL
#define SYM_TOOL

#include "../Vec2/Vec2.h"
#include "../Color.h"
#include "../Keys.h"
#include "../Standart/ToolI.h"

class RenderTarget;

class Tool : public plugin::ToolI
{
    
protected :
    plugin::Vec2 start_pos;
    plugin::Vec2 last_pos;
    bool   drawing;

public :
    Tool() :
    start_pos (plugin::Vec2(-1, -1)),
    last_pos  (plugin::Vec2(-1, -1)),
    drawing   (false)
    {};

    virtual void PaintOnPress  (RenderTarget&  data,  RenderTarget& tmp, 
                                MouseContext mouse, plugin::Color color) = 0;
    virtual void PaintOnMove   (RenderTarget&  data,  RenderTarget& tmp, 
                                MouseContext mouse, plugin::Color color) = 0;
    virtual void PaintOnRelease(RenderTarget&  data,  RenderTarget& tmp, 
                                MouseContext mouse, plugin::Color color) = 0;
    virtual void Disable       (RenderTarget&  data,  RenderTarget& tmp, 
                                MouseContext mouse, plugin::Color color) = 0;
};

#endif //SYM_TOOL