#ifndef SYM_RENDER_TARGET
#define SYM_RENDER_TARGET

#include <string.h>

#include "../Standart/Standart.h"
#include "../Standart/Standart.h"
#include "../Texture/Texture.h"
#include "../Font/Font.h"
#include "../Standart/Standart.h"

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
    void    clear(plugin::Color color) override;

    void             display()    override;
    void             clear()      override;
    plugin::Texture* getTexture() override;


    void setPixel   (plugin::Vec2 pos, plugin::Color color)   override;

    void drawLine   (plugin::Vec2 point1, plugin::Vec2 point2, 
                     plugin::Color color)                     override;

    void drawRect   (plugin::Vec2 pos, plugin::Vec2 size, 
                     plugin::Color color)                     override;

    void drawEllipse(plugin::Vec2 pos, plugin::Vec2 size, 
                     plugin::Color color)                     override;     

    void drawTexture(plugin::Vec2 pos, plugin::Vec2 size, 
                     const plugin::Texture *texture)          override;
                     
    void drawText   (plugin::Vec2 pos, const char *content, 
                     uint16_t char_size, plugin::Color color) override;

    void setTexture(plugin::Texture* new_texture) override
    {
        drawTexture(plugin::Vec2(0, 0), plugin::Vec2(new_texture->width, 
                                                     new_texture->height), 
                                        new_texture);
    }
};

#endif //SYM_RENDER_TARGET