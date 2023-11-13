#ifndef SYM_RENDERABLE
#define SYM_RENDERABLE

#include "../RenderTarget/RenderTarget.h"
#include "../Vec2/Vec2.h"

class Renderable
{

public:
    Renderable() {};
    
    virtual void Render(RenderTarget* render_target) = 0;
};

#endif //SYM_RENDERABLE