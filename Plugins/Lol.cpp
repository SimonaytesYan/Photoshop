#include "Lol.h"

WhiteAndBlackPlugin::WhiteAndBlackPlugin(plugin::App* app) :
app (app)
{ 
    filter = new WhiteAndBlackFilter();

    name = "Lol";
    type = plugin::InterfaceType::Filter;
}

plugin::Plugin* getInstance(plugin::App *app)
{
    return new WhiteAndBlackPlugin(app);
}

plugin::Array<const char*> WhiteAndBlackFilter::getParamNames()
{ 
    return plugin::Array<const char*>(0, nullptr); 
}

plugin::Array<double> WhiteAndBlackFilter::getParams()
{ 
    return plugin::Array<double>(0, nullptr); 
}

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

    rt->drawTexture(plugin::Vec2(0, 0), 
                    plugin::Vec2(texture->width, texture->height), 
                    texture);
}
