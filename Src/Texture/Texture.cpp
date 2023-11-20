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

plugin::Vec2 Texture::GetSize()
{
    return plugin::Vec2(data.getSize().x, data.getSize().y);
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

plugin::Vec2 Image::GetSize()
{
    return plugin::Vec2(data.getSize().x, data.getSize().y);
}

u_int8_t* Image::GetPixelArray(plugin::VectorI& size)
{
    size = plugin::Vec2(data.getSize().x, data.getSize().y);
    return GetPixelArray();
}

u_int8_t* Image::GetPixelArray()
{
    return (u_int8_t*)data.getPixelsPtr();
}

sf::Image Image::GetImage()
{
    return data;
}