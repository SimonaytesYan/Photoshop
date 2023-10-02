#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../../../Color.h"
#include "../Widget.h"

class Button : public Widget
{
    void*  args;
    void   (*on_click)(void*);
    Vector size;
    Color  color;

public :
    Button(Vector _position, 
           Vector _size, 
           Color  _color,
           void  (*_on_click)(void*) = nullptr, 
           void* _args               = nullptr);
    
    virtual void Render      (RenderTarget* render_target) override;
            bool OnMousePress(MouseCondition mouse)        override;
            bool Inside_p    (Vector v);
};

#endif //SYM_BUTTON