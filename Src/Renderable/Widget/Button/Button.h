#ifndef SYM_BUTTON
#define SYM_BUTTON

#include "../../../Color.h"
#include "../Widget.h"

struct ButtonFunction
{
    virtual void operator()() = 0;
    virtual ~ButtonFunction()
    {}
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

    plugin::Color           background_color;       //use only if texture_button == false

public :
    Button(plugin::Vec2          _position, 
           plugin::Vec2          _size, 
           Texture         _texture,
           Texture         _press_texture,
           ButtonFunction*  _on_press   = nullptr,
           ButtonFunction*  _on_release = nullptr);
    Button(plugin::Vec2   _position, 
           plugin::Vec2   _size, 
           plugin::Color    _background_color,
           ButtonFunction* _on_press   = nullptr,
           ButtonFunction* _on_release = nullptr);
    ~Button();

    void ChangePressFunction(ButtonFunction* new_on_press)
    {
        on_press = new_on_press;
    }
       
    virtual void render        (RenderTarget* render_target) override;
            bool onMousePress  (plugin::MouseContext mouse)        override;
            bool onMouseRelease(plugin::MouseContext mouse)        override;
            bool onMouseMove   (plugin::MouseContext mouse)        override;
};

class TextButton : public Button
{
    public : 
    TextButton(plugin::Vec2   _position, plugin::Vec2   _size, 
               Texture  _texture,  Texture  _press_texture,
               Font font, int character_size, const char* text = "Button",
               plugin::Color text_color = plugin::Color(0, 0, 0), 
               plugin::Color background_color = plugin::Color(255, 255, 255),
               ButtonFunction*  _on_press   = nullptr,
               ButtonFunction*  _on_release = nullptr);
    
    TextButton(plugin::Vec2   _position, plugin::Vec2   _size, 
               plugin::Color    _background_color,
               Font font, int character_size, const char* text = "Button",
               plugin::Color text_color = plugin::Color(0, 0, 0), 
               ButtonFunction*  _on_press   = nullptr,
               ButtonFunction*  _on_release = nullptr);
};

#endif //SYM_BUTTON