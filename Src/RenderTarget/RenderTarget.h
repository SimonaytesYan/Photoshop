#ifndef SYM_RENDER_TARGET
#define SYM_RENDER_TARGET

#include "../Color.h"
#include "../Vec2/Vec2.h"
#include "../Texture/Texture.h"
#include "../Font/Font.h"
class RegionSet;

class RenderTarget
{
    sf::RenderTexture data;

public :
    RenderTarget(Vec2 size);

    void SetPixel     (Vec2 position,           Color color, const RegionSet& rend_set);
    void DrawCircle   (Vec2 position, double r, Color color, const RegionSet& rend_set);
    void DrawLine     (Vec2 v0, Vec2 v1,      Color color, const RegionSet& rend_set);
    void DrawRect     (Vec2 position, Vec2 size,
                       const RegionSet& rend_set, 
                       Color fill_color = Color(255, 255, 255),
                       int border_size = 0,
                       Color border_color = Color(0, 0, 0));
    void DrawSprite   (Vec2 position, Texture texture, const RegionSet& rend_set);
    void DrawText     (Vec2 position, Font font, const char* text, 
                       int character_size, Color color,
                       const RegionSet& rend_set);
    void DrawRegionSet(const RegionSet& reg_set, Color color, size_t color_type = 0);


    void SetPixel     (Vec2 position,           Color color);
    void DrawCircle   (Vec2 position, double r, Color color, 
                       Vec2 scale = Vec2(1, 1));
    void DrawLine     (Vec2 v0, Vec2 v1, Color color);
    void DrawRect     (Vec2 position, Vec2 size,
                       Color fill_color = Color(255, 255, 255),
                       int border_size = 0,
                       Color border_color = Color(0, 0, 0));
    void DrawSprite   (Vec2 position, Texture texture);
    void DrawText     (Vec2 position, Font font, const char* text, 
                       int character_size, Color color);

    Texture GetTexture();
    void    Display(sf::RenderWindow* window);
    void    Display();
    void    Draw(sf::RenderWindow* window);
    void    Clear();
    void    Clear(Color color);
};

#endif //SYM_RENDER_TARGET