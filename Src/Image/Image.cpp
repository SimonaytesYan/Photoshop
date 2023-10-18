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

Vector Image::GetSize()
{
    return Vector(data.getSize().x, data.getSize().y);
}

u_int8_t* Image::GetPixelArray(VectorI& size)
{
    size = Vector(data.getSize().x, data.getSize().y);
    return (u_int8_t*)data.getPixelsPtr();
}

sf::Image Image::GetImage()
{
    return data;
}