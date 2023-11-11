#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../../../Color.h"
#include "../Widget.h"

struct ButtonFunction
{
    virtual void operator()() = 0;
    virtual ~ButtonFunction() = 0;
};

class Button : public Widget
{
protected :
    ButtonFunction* on_press;
    ButtonFunction* on_release;
    bool            pressed;
    bool            use_texture;
    
    Texture         texture;                //use only if texture_button == true
    Texture         press_texture;          //use only if texture_button == true

    Color           background_color;       //use only if texture_button == false

public :
    Button(Vector          _position, 
           Vector          _size, 
           Texture         _texture,
           Texture         _press_texture,
           ButtonFunction*  _on_press   = nullptr,
           ButtonFunction*  _on_release = nullptr);
    Button(Vector   _position, 
           Vector   _size, 
           Color    _background_color,
           ButtonFunction* _on_press   = nullptr,
           ButtonFunction* _on_release = nullptr);
    ~Button();

    void ChangePressFunction(ButtonFunction* new_on_press)
    {
        on_press = new_on_press;
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
               ButtonFunction*  _on_press   = nullptr,
               ButtonFunction*  _on_release = nullptr);
    
    TextButton(Vector   _position, Vector   _size, 
               Color    _background_color,
               Font font, int character_size, const char* text = "Button",
               Color text_color = Color(0, 0, 0), 
               ButtonFunction*  _on_press   = nullptr,
               ButtonFunction*  _on_release = nullptr);
};

#endif //SYM_BUTTON