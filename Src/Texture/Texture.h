#ifndef SYM_TEXTURE
#define SYM_TEXTURE

#include <cstdint>
#include <string.h>

#include <SFML/Graphics.hpp>
#include "../Standart/Standart.h"
#include "../Vec2.h"

class Image;

class Texture
{
    sf::Texture data;

public:
    Texture()                     { data = sf::Texture(); }
    Texture(sf::Texture new_data) { data = new_data;      }
    Texture(plugin::Texture text);

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
    Image(plugin::Texture text);

    void         Create      (int width, int height, 
                              plugin::Color color = plugin::Color(0, 0, 0));
    bool         LoadFromFile(const char* filename);
    sf::Image    GetImage    ();
    plugin::Vec2 getSize     ();

    u_int8_t* GetPixelArray();
    u_int8_t* GetPixelArray(VectorI& size);
};


#endif //SYM_TEXTURE