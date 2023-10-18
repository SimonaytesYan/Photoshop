#include <string.h>

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

u_int8_t* Texture::GetPixelArray(VectorI& size)
{
    sf::Image image(data.copyToImage());
    size = Vector(image.getSize().x, image.getSize().y);

    u_int8_t* pixels = (u_int8_t*)calloc(sizeof(u_int8_t), 
                                         image.getSize().x * image.getSize().y * 4);
    memcpy(pixels, image.getPixelsPtr(), image.getSize().x * image.getSize().y * 4);
    return pixels;
}

sf::Texture* Texture::GetTexture()
{
    return &data;
}