#ifndef SYM_RENDERABLE
#define SYM_RENDERABLE

#include "../RenderTarget/RenderTarget.h"
#include "../Standart/Standart.h"

class Renderable
{

public:
    Renderable() {};
    
    virtual void render(RenderTarget* render_target) = 0;
};

#endif //SYM_RENDERABLE