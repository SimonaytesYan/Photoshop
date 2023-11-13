#ifndef SYM_IMAGE
#define SYM_IMAGE

#include <SFML/Graphics.hpp>

#include "../Vec2/Vec2.h"

class Texture;

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

#endif //SYM_IMAGE