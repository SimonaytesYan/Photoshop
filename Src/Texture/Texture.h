#ifndef SYM_TEXTURE
#define SYM_TEXTURE

#include <SFML/Graphics.hpp>

#include "../Vector/Vector.h"

class Texture
{
    sf::Texture data;

public:
    Texture()                     { data = sf::Texture(); }
    Texture(sf::Texture new_data) { data = new_data;      }

    bool            Create      (int width, int height);
    bool            LoadFromFile(const char* filename);
    sf::Texture*    GetTexture  ();
    Vector          GetSize();
    const u_int8_t* GetPixelArray(Vector& size);     
};

#endif //SYM_TEXTURE