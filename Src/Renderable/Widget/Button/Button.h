#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../../../Color.h"
#include "../Widget.h"

class Button : public Widget
{
    void*  args;
    void*  on_click;
    Vector size;
    Color  color;

public :
    Button(Vector _position, 
           Vector _size, 
           Color  _color,
           void* _on_click = nullptr, 
           void* _args = nullptr);
    
    virtual void Render(RenderTarget* render_target) override;
};

#endif //SYM_BUTTON