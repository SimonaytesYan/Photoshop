#ifndef SYM_TEXTURE
#define SYM_TEXTURE

#include <SFML/Graphics.hpp>

#include "../Vec2/Vec2.h"

class Image;

class Texture
{
    sf::Texture data;

public:
    Texture()                     { data = sf::Texture(); }
    Texture(sf::Texture new_data) { data = new_data;      }

    bool            Create      (int width, int height);
    bool            LoadFromFile(const char* filename);
    sf::Texture*    GetTexture  ();
    bool            LoadFromImage(Image img);
    Vec2          GetSize(); 
};

#endif //SYM_TEXTURE