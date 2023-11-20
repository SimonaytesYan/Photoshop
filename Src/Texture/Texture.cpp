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

Vec2 Texture::GetSize()
{
    return Vec2(data.getSize().x, data.getSize().y);
}

bool Texture::LoadFromImage(Image img)
{
    return data.loadFromImage(img.GetImage());
}

sf::Texture* Texture::GetTexture()
{
    return &data;
}

//--------------------------------IMAGE-----------------------------------------

Image::Image(Texture text)
{
    data = text.GetTexture()->copyToImage();
}

void Image::Create(int width, int height)
{
    data.create(width, height);
}

bool Image::LoadFromFile(const char* filename)
{
    return data.loadFromFile(filename);
}

Vec2 Image::GetSize()
{
    return Vec2(data.getSize().x, data.getSize().y);
}

u_int8_t* Image::GetPixelArray(VectorI& size)
{
    size = Vec2(data.getSize().x, data.getSize().y);
    return (u_int8_t*)data.getPixelsPtr();
}

sf::Image Image::GetImage()
{
    return data;
}