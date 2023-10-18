#ifndef SYM_IMAGE
#define SYM_IMAGE

#include <SFML/Graphics.hpp>

#include "../Vector/Vector.h"

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
    sf::Image GetImage  ();
    Vector    GetSize();    
    u_int8_t* GetPixelArray(VectorI& size);
};

#endif //SYM_IMAGE