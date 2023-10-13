#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../../../Color.h"
#include "../Widget.h"

class Button : public Widget
{
    void*   args;
    void    (*on_click)(void*);
    bool    use_texture;
    Texture texture;                //use only if texture_button == false
    Color   background_color;       //use only if texture_button == false

public :
    Button(Vector   _position, 
           Vector   _size, 
           Texture  _texture,
           void  (*_on_click)(void*) = nullptr, 
           void* _args               = nullptr);
    Button(Vector   _position, 
           Vector   _size, 
           Color    _background_color,
           void  (*_on_click)(void*) = nullptr, 
           void* _args               = nullptr);
    ~Button();

    virtual void Render      (RenderTarget* render_target) override;
            bool OnMousePress(MouseCondition mouse)        override;
            bool InsideP     (Vector v);
};

#endif //SYM_BUTTON