#include <string.h>

#include "Texture.h"

Texture::Texture(plugin::Texture text) 
{
    Image img(text);
    LoadFromImage(img);
}

bool Texture::Create(int width, int height)
{
    return data.create(width, height);
}

bool Texture::LoadFromFile(const char* filename)
{
    return data.loadFromFile(filename);
}

plugin::Vec2 Texture::getSize()
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

Image::Image(plugin::Texture text) 
{ 
    data.create(text.width, text.height);
    memcpy((void*)data.getPixelsPtr(),
           text.pixels,
           text.width * text.height * sizeof(plugin::Color));
}

Image::Image(Texture text)
{
    data = text.GetTexture()->copyToImage();
}

void Image::Create(int width, int height, plugin::Color color)
{
    data.create(width, height, sf::Color(color.r, color.g, color.b, color.a));
}

bool Image::LoadFromFile(const char* filename)
{
    return data.loadFromFile(filename);
}

plugin::Vec2 Image::getSize()
{
    return plugin::Vec2(data.getSize().x, data.getSize().y);
}

u_int8_t* Image::GetPixelArray(VectorI& size)
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