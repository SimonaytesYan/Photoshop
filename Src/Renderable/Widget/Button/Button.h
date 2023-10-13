#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../../../Color.h"
#include "../Widget.h"

class Button : public Widget
{
    void*   args_press;
    void*   args_release;
    void    (*on_press)(void*);
    void    (*on_release)(void*);
    bool    pressed;
    bool    use_texture;
    Texture texture;                //use only if texture_button == true
    Texture press_texture;          //use only if texture_button == true

    Color   background_color;       //use only if texture_button == false

public :
    Button(Vector   _position, 
           Vector   _size, 
           Texture  _texture,
           Texture  _press_texture,
           void  (*_on_press)(void*)   = nullptr, 
           void* _args_press           = nullptr,
           void  (*_on_release)(void*) = nullptr,
           void* _args_release         = nullptr);
    Button(Vector   _position, 
           Vector   _size, 
           Color    _background_color,
           void  (*_on_press)(void*)   = nullptr, 
           void* _args_press           = nullptr,
           void  (*_on_release)(void*) = nullptr,
           void*  _args_release        = nullptr);
    ~Button();

    virtual void Render        (RenderTarget* render_target) override;
            bool OnMousePress  (MouseCondition mouse)        override;
            bool OnMouseRelease(MouseCondition mouse)        override;
            bool OnMouseMove   (MouseCondition mouse)        override;
            bool InsideP       (Vector v);
};

#endif //SYM_BUTTON