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

    bool          Create      (int width, int height);
    bool          LoadFromFile(const char* filename);
    sf::Texture*  GetTexture  ();
    bool          LoadFromImage(Image img);
    Vec2          GetSize(); 
};

class Image
{
    sf::Image data;

public:
    Image(Texture text);
    Image()                   { data = sf::Image(); }
    Image(sf::Image new_data) { data = new_data;      }

    void      Create      (int width, int height);
    bool      LoadFromFile(const char* filename);
    sf::Image GetImage    ();
    Vec2    GetSize     ();

    // Calloc buffer to pixels 
    // You should free it after using
    u_int8_t* GetPixelArray(VectorI& size);
};

#endif //SYM_TEXTURE