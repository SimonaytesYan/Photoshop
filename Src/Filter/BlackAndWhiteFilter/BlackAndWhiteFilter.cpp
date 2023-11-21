#include "BlackAndWhiteFilter.h"
#include "../../Useful.h"
#include "../../Texture/Texture.h"

plugin::Array<const char*> BlackAndWhiteFilter::getParamNames()
{
    return param_names;
}

void BlackAndWhiteFilter::apply(plugin::RenderTargetI* rt)
{
    plugin::VectorI   size(0, 0);
    Image     img(((RenderTarget*)rt)->GetTexture());
    u_int8_t* pixels = img.GetPixelArray(size);

    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            plugin::Color* cur_color = GetC(pixels, size, plugin::VectorI(x, y));

            int pixel_color = (cur_color->r + cur_color->g + cur_color->b) / 3;
            cur_color->r = pixel_color;
            cur_color->g = pixel_color;
            cur_color->b = pixel_color;
        }
    }

    Texture texture;
    texture.LoadFromImage(img);
    ((RenderTarget*)rt)->DrawSprite(plugin::Vec2(0, 0), texture);
}

void BlackAndWhiteFilter::setParams(plugin::Array<double> params)
{}
