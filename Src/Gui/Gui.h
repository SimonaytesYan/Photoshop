#ifndef SYM_GUI
#define SYM_GUI

#include "../Standart/Standart.h"
#include "../Renderable/Widget/Widget.h"
#include "../Renderable/Widget/RectangleWidget/RectangleWidget.h"

class Gui : public plugin::GuiI
{
    Widget*          root;
    RectangleWidget* rt_widget;

public:

    Gui(Widget* root = nullptr) :
    root (root)
    {}

    plugin::Vec2 getSize() override
    { return root->getSize(); }
    plugin::RenderTargetI* getRenderTarget(plugin::Vec2 size, 
                                           plugin::Vec2 pos, 
                                           plugin::Plugin *self) override;

    void createParamWindow(plugin::Array<const char*> param_names, 
                           plugin::Interface*         self) override;

    plugin::WidgetI* getRoot() override
    { return root; }
};

#endif //SYM_GUI
