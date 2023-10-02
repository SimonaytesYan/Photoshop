#ifndef SYM_FONT
#define SYM_FONT

#include <SFML/Graphics.hpp>

class Font 
{
    sf::Font font;

public :
    void      LoadFont(const char* file);
    sf::Font* GetFont();
};

#endif //SYM_FONT