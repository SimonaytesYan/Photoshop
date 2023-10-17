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

const u_int8_t* Texture::GetPixelArray(Vector& size)
{
    sf::Image image(data.copyToImage());
    size = Vector(image.getSize().x, image.getSize().y);
    return image.getPixelsPtr();
}

sf::Texture* Texture::GetTexture()
{
    return &data;
}