#include "Texture.h"

bool Texture::Create(int width, int height)
{
    return data.create(width, height);
}

bool Texture::LoadFromFile(const char* filename)
{
    return data.loadFromFile(filename);
}

Vector Texture::GetSize()
{
    return Vector(data.getSize().x, data.getSize().y);
}

sf::Texture* Texture::GetTexture()
{
    return &data;
}