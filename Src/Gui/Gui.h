#ifndef SYM_GUI
#define SYM_GUI

#include "../Standart/Standart.h"
#include "../Renderable/Widget/Widget.h"
#include "../Renderable/Widget/RectangleWidget/RectangleWidget.h"

class Gui : public plugin::GuiI
{
    DynArray<plugin::Plugin*> plugins;
    Widget*                   root;
    RectangleWidget*          rt_widget;

public:

    Gui(Widget* root = nullptr) :
    root (root)
    { }

    void AddPlugin(plugin::Plugin* new_plugin)
    {
        plugins.PushBack(new_plugin);
    }

    DynArray<plugin::Plugin*>& GetPlugins()
    {
        return plugins;
    }

    plugin::WidgetI* getRoot() const override
    { return root; }

    void createWidgetI(plugin::PluginWidgetI* widget) override;

    plugin::Plugin* queryPlugin(uint64_t id) override;

    plugin::Texture* loadTextureFromFile(const char *filename) override;
};

#endif //SYM_GUI
