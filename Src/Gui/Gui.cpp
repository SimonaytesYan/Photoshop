#include "Gui.h"
#include "../ClipRegion/ClipRegion.h"
#include "../RegionSet/RegionSet.h"

void createWidgetI(plugin::PluginWidgetI* widget)
{

}

plugin::Plugin* queryPlugin(uint64_t id)
{

}

plugin::Texture* loadTextureFromFile(const char *filename)
{
    Image image;
    image.LoadFromFile(filename);

    plugin::Texture* texture = new plugin::Texture();
    texture->width  = image.getSize().x; 
    texture->height = image.getSize().y;
    texture->pixels = new plugin::Color[texture->width * texture->height];
    
    memcpy(texture->pixels, image.GetPixelArray(), 
           sizeof(plugin::Color) * texture->width * texture->height);
    
    return texture;
}
