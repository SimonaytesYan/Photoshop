#ifndef SYM_RENDER_TARGET
#define SYM_RENDER_TARGET

#include "../Color.h"
#include "../Vector/Vector.h"
#include "../Texture/Texture.h"
#include "../Font/Font.h"
class RegionSet;

class RenderTarget
{
    sf::RenderTexture data;

public :
    RenderTarget(Vector size);

    void SetPixel     (Vector position, Color color);
    void DrawCircle   (Vector position, double r, Color color);
    void DrawLine     (Vector v0, Vector v1);
    void DrawRect     (Vector position, Vector size, 
                       Color fill_color = Color(255, 255, 255),
                       int border_size = 0,
                       Color border_color = Color(0, 0, 0));
    void DrawSprite   (Vector position, Texture texture);
    void DrawText     (Vector position, Font font, const char* text, int character_size);
    void DrawRegionSet(const RegionSet& reg_set, int color_type);

    void Display(sf::RenderWindow* window);
    void Draw(sf::RenderWindow* window);
    void Clear();
};

#endif //SYM_RENDER_TARGET