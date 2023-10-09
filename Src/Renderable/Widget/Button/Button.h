#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../../../Color.h"
#include "../Widget.h"

class Button : public Widget
{
    void*   args;
    void    (*on_click)(void*);
    Vector  size;
    Texture texture;

public :
    Button(Vector   _position, 
           Vector   _size, 
           Texture  _texture         = Texture(),
           void  (*_on_click)(void*) = nullptr, 
           void* _args               = nullptr);
    ~Button();

    virtual void Render      (RenderTarget* render_target) override;
            bool OnMousePress(MouseCondition mouse)        override;
            bool InsideP    (Vector v);
};

#endif //SYM_BUTTON