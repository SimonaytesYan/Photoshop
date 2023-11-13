#include <string.h>

#include "Image.h"
#include "../Texture/Texture.h"

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