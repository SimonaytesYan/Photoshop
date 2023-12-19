#include "Gui.h"
#include "../ClipRegion/ClipRegion.h"
#include "../RegionSet/RegionSet.h"

void Gui::createWidgetI(plugin::PluginWidgetI* widget)
{
    PluginWidget* plug_widget = new PluginWidget(widget);
    widget->host = plug_widget;
    root->registerSubWidget(plug_widget);  
    
    fprintf(stderr, "CreateWidgetI root = %p\nwidget->host = %p\n\n", root, plug_widget);
}

plugin::Plugin* Gui::queryPlugin(uint64_t id)
{
    for (int i = 0; i < plugins.GetLength(); i++)
    {
        if (plugins[i]->id == id)
            return plugins[i];
    }

    return nullptr;
}

plugin::Texture* Gui::loadTextureFromFile(const char *filename)
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
