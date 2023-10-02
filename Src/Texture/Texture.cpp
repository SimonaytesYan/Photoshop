#include "Texture.h"

bool Texture::Create(int width, int height)
{
    return data.create(width, height);
}

bool Texture::loadFromFile(const char* filename)
{
    return data.loadFromFile(filename);
}

sf::Texture* Texture::GetTexture()
{
    return &data;
}