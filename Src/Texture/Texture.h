#ifndef SYM_TEXTURE
#define SYM_TEXTURE

#include <cstdint>
#include <string.h>

#include <SFML/Graphics.hpp>
#include "../Vec2/Vec2.h"
#include "../Color.h"

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
    plugin::Vec2  getSize(); 
};

class Image
{
    sf::Image data;

public:
    Image(Texture text);
    Image()                   { data = sf::Image(); }
    Image(sf::Image new_data) { data = new_data;      }

    void         Create      (int width, int height);
    bool         LoadFromFile(const char* filename);
    sf::Image    GetImage    ();
    plugin::Vec2 getSize     ();

    u_int8_t* GetPixelArray();
    u_int8_t* GetPixelArray(VectorI& size);
};

namespace plugin
{
    struct Texture 
    {
        uint64_t height;
        uint64_t width;

        Color *pixels;

        Texture()
        {
            width  = 0;
            height = 0;
            pixels = nullptr;
        }

        Texture(const Texture& texture)
        {
            height = texture.height;
            width  = texture.width;

            pixels = new Color[height * width];
            memcpy(pixels, texture.pixels, sizeof(Color) * height * width);
        }
    };
}


#endif //SYM_TEXTURE