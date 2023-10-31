#include "BlackAndWhiteFilter.h"
#include "../../Useful.h"
#include "../../Image/Image.h"

DynArray<const char*> BlackAndWhiteFilter::GetParamNames()
{
    DynArray<const char*> param_names(0);

    return param_names;
}

void BlackAndWhiteFilter::Apply(RenderTarget& rt)
{
    VectorI   size(0, 0);
    Image     img(rt.GetTexture());
    u_int8_t* pixels = img.GetPixelArray(size);

    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            Color* cur_color = GetC(pixels, size, VectorI(x, y));

            int pixel_color = (cur_color->r + cur_color->g + cur_color->b) / 3;
            cur_color->r = pixel_color;
            cur_color->g = pixel_color;
            cur_color->b = pixel_color;
        }
    }

    Texture texture;
    texture.LoadFromImage(img);
    rt.DrawSprite(Vector(0, 0), texture);
}

void BlackAndWhiteFilter::SetParams(const DynArray<double>& params)
{}
