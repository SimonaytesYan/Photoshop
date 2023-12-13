#ifndef SYM_HORIZONTAL_MENU
#define SYM_HORIZONTAL_MENU

#include "../Menu.h"

class HorizontalMenu : public Menu
{

public:

    HorizontalMenu(Widget* widget) :
    Menu(widget)
    {
        fprintf(stderr, "Static Hor menu expanded = %d\n", expanded);
    }

    HorizontalMenu(Button* button, bool static_menu) : 
    Menu(button, static_menu)
    {}

    void registerSubWidget(plugin::WidgetI* new_widget) override;
};

#endif //SYM_HORIZONTAL_MENU