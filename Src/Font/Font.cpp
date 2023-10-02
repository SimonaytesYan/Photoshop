#include "Font.h"

void Font::LoadFont(const char* file)
{
    font.loadFromFile(file);
}

sf::Font* Font::GetFont()
{
    return &font;
}
