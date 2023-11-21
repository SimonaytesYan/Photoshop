#include "BrightnessFilter.h"
#include "../../Useful.h"
#include "../../Texture/Texture.h"

DynArray<const char*> BrightnessFilter::GetParamNames()
{
    DynArray<const char*> param_names(0);
    param_names.PushBack("brightness");

    return param_names;
}

void BrightnessFilter::apply(plugin::RenderTargetI* rt)
{
    plugin::VectorI   size(0, 0);
    Image     img(rt.GetTexture());
    u_int8_t* pixels = img.GetPixelArray(size);

    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            plugin::Color* cur_color = GetC(pixels, size, plugin::VectorI(x, y));

            cur_color->r = BorderPlus(cur_color->r, brightness, 255);
            cur_color->g = BorderPlus(cur_color->g, brightness, 255);
            cur_color->b = BorderPlus(cur_color->b, brightness, 255);
        }
    }

    Texture texture;
    texture.LoadFromImage(img);
    rt.DrawSprite(plugin::Vec2(0, 0), texture);
}

void BrightnessFilter::setParams(plugin::Array<double> params)
{
    if (params.GetLength() == 1)
        brightness = params[0];
}
