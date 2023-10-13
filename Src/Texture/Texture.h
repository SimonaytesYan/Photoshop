#ifndef SYM_TEXTURE
#define SYM_TEXTURE

#include <SFML/Graphics.hpp>

#include "../Vector/Vector.h"

class Texture
{
    sf::Texture data;

public:
    bool         Create      (int width, int height);
    bool         LoadFromFile(const char* filename);
    sf::Texture* GetTexture  ();
    Vector       GetSize();
};

#endif //SYM_TEXTURE