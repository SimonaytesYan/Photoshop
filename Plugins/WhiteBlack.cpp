#include <stdio.h>
#include "WhiteBlack.h"

extern "C" plugin::Plugin* getInstance(plugin::App *app)
{
    return new SymWhiteAndBlackPlugin(app);
}

SymWhiteAndBlackPlugin::SymWhiteAndBlackPlugin(plugin::App* app) :
app (app)
{ 
    filter = new WhiteAndBlackFilter();

    name = "Lol";
    type = plugin::InterfaceType::Filter;
}

plugin::Array<const char*> WhiteAndBlackFilter::getParamNames() const
{ 
    return {0, nullptr}; 
}

plugin::Array<double> WhiteAndBlackFilter::getParams() const
{ 
    return {0, nullptr}; 
}

void WhiteAndBlackFilter::setParams(plugin::Array<double> params)
{ }

void WhiteAndBlackFilter::apply(plugin::RenderTargetI* rt)
{
    plugin::Texture* texture = rt->getTexture(); 
    plugin::Color*   pixels  = texture->pixels;

    for (int y = 0; y < texture->height; y++)
    {
        for (int x = 0; x < texture->width; x++)
        {
            plugin::Color* cur_color = &pixels[y * texture->width + x];

            int pixel_color = cur_color->r * 0.3 + 
                              cur_color->g * 0.6 + 
                              cur_color->b * 0.1;
            cur_color->r = pixel_color;
            cur_color->g = pixel_color;
            cur_color->b = pixel_color;
        }
    }


    plugin::Vec2 pos  = {0, 0};
    plugin::Vec2 size = {(double)texture->width, (double)texture->height};
    rt->drawTexture(pos, size, texture);

    delete[] texture->pixels;
    delete texture;
}
