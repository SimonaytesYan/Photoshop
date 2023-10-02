#ifndef SYM_RENDER_TARGET
#define SYM_RENDER_TARGET

#include "../Color.h"
#include "../Vector/Vector.h"
#include "../Texture/Texture.h"

class RenderTarget
{
    sf::RenderTexture data;

public :
    RenderTarget(Vector size);

    void SetPixel  (Vector position, Color color);
    void DrawCircle(Vector position, double r, Color color);
    void DrawLine  (Vector v0, Vector v1);
    void DrawRect  (Vector position, Vector size, 
                    Color fill_color = Color(255, 255, 255));
    void DrawSprite(Vector position, Texture texture);
    void DrawText  ();

    void Display(sf::RenderWindow* window);
    void Draw(sf::RenderWindow* window);
};

#endif //SYM_RENDER_TARGET