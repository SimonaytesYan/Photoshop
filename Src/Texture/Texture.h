#ifndef SYM_TEXTURE
#define SYM_TEXTURE

#include <SFML/Graphics.hpp>

class Texture
{
    sf::Texture data;

public:
    bool         Create      (int width, int height);
    bool         loadFromFile(const char* filename);
    sf::Texture* GetTexture  ();
};

#endif //SYM_TEXTURE