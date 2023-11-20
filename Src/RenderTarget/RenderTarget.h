#ifndef SYM_RENDER_TARGET
#define SYM_RENDER_TARGET

#include <string.h>

#include "../Color.h"
#include "../Vec2/Vec2.h"
#include "../Texture/Texture.h"
#include "../Font/Font.h"
#include "../Standart/RenderTargetI.h"

class RegionSet;

class RenderTarget : plugin::RenderTargetI
{
    static Font standard_font;

    sf::RenderTexture data;

public :
    
    RenderTarget(plugin::Vec2 size);

    void SetPixel     (plugin::Vec2 position,           plugin::Color color, const RegionSet& rend_set);
    void DrawCircle   (plugin::Vec2 position, double r, plugin::Color color, const RegionSet& rend_set);
    void DrawLine     (plugin::Vec2 v0, plugin::Vec2 v1,      plugin::Color color, const RegionSet& rend_set);
    void DrawRect     (plugin::Vec2 position, plugin::Vec2 size,
                       const RegionSet& rend_set, 
                       plugin::Color fill_color = plugin::Color(255, 255, 255),
                       int border_size = 0,
                       plugin::Color border_color = plugin::Color(0, 0, 0));
    void DrawSprite   (plugin::Vec2 position, Texture texture, const RegionSet& rend_set);
    void DrawText     (plugin::Vec2 position, Font font, const char* text, 
                       int character_size, plugin::Color color,
                       const RegionSet& rend_set);
    void DrawRegionSet(const RegionSet& reg_set, plugin::Color color, size_t color_type = 0);


    void SetPixel     (plugin::Vec2 position,           plugin::Color color);
    void DrawCircle   (plugin::Vec2 position, double r, plugin::Color color, 
                       plugin::Vec2 scale = plugin::Vec2(1, 1));
    void DrawLine     (plugin::Vec2 v0, plugin::Vec2 v1, plugin::Color color);
    void DrawRect     (plugin::Vec2 position, plugin::Vec2 size,
                       plugin::Color fill_color = plugin::Color(255, 255, 255),
                       int border_size = 0,
                       plugin::Color border_color = plugin::Color(0, 0, 0));
    void DrawSprite   (plugin::Vec2 position, Texture texture);
    void DrawText     (plugin::Vec2 position, Font font, const char* text, 
                       int character_size, plugin::Color color);

    Texture GetTexture();
    void    display(sf::RenderWindow* window);
    void    clear(plugin::Color color);

    void             display()    override;
    void             clear()      override;
    plugin::Texture* getTexture() override;

    void setPixel   (plugin::Vec2 pos, plugin::Color color)              override
    { SetPixel(pos, color); }

    void drawLine   (plugin::Vec2 point1, plugin::Vec2 point2, plugin::Color color) override
    { DrawLine(point1, point2, color); }

    void drawRect   (plugin::Vec2 pos, plugin::Vec2 size, plugin::Color color)   override
    { DrawRect(pos, size, color); }

    void drawEllipse(plugin::Vec2 pos, plugin::Vec2 size, plugin::Color color)   override
    { DrawCircle(pos, size.x, color, plugin::Vec2(1, size.y / size.x));  }
        
    void drawTexture(plugin::Vec2 pos, plugin::Vec2 size, 
                     const plugin::Texture *texture)     override
    {
        Image img;
        img.Create(size.x, size.y);
        memcpy(img.GetPixelArray(), 
               texture->pixels, 
               size.x * size.y * sizeof(plugin::Color));
        
        Texture my_texture;
        my_texture.LoadFromImage(img);

        DrawSprite(pos, my_texture);
    }

    void drawText   (plugin::Vec2 pos, const char *content, 
                     uint16_t char_size, plugin::Color color)    override
    { DrawText(pos, standard_font, content, char_size, color); }
};

#endif //SYM_RENDER_TARGET