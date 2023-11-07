#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../../../Color.h"
#include "../Widget.h"

class Button : public Widget
{
protected :
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

    void ChangePressFunction(void (*new_on_press)(void*), void* new_args_press)
    {
        on_press   = new_on_press;
        args_press = new_args_press;
    }
       
    virtual void Render        (RenderTarget* render_target) override;
            bool OnMousePress  (MouseCondition mouse)        override;
            bool OnMouseRelease(MouseCondition mouse)        override;
            bool OnMouseMove   (MouseCondition mouse)        override;
};

class TextButton : public Button
{
    public : 
    TextButton(Vector   _position, Vector   _size, 
               Texture  _texture,  Texture  _press_texture,
               Font font, int character_size, const char* text = "Button",
               Color text_color = Color(0, 0, 0), 
               Color background_color = Color(255, 255, 255),
               void  (*_on_press)(void*)   = nullptr, 
               void* _args_press           = nullptr,
               void  (*_on_release)(void*) = nullptr,
               void* _args_release         = nullptr);
    
    TextButton(Vector   _position, Vector   _size, 
               Color    _background_color,
               Font font, int character_size, const char* text = "Button",
               Color text_color = Color(0, 0, 0), 
               void  (*_on_press)(void*)   = nullptr, 
               void* _args_press           = nullptr,
               void  (*_on_release)(void*) = nullptr,
               void*  _args_release        = nullptr);
};

#endif //SYM_BUTTON