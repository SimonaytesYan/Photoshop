#ifndef SYM_HORIZONTAL_MENU
#define SYM_HORIZONTAL_MENU

#include "../Menu.h"

class HorizontalMenu : public Menu
{

public:

    HorizontalMenu(Widget* widget) :
    Menu(widget)
    {}

    HorizontalMenu(Button* button, bool static_menu) : 
    Menu(button, static_menu)
    {}

    void registerSubWidget(Widget* new_widget) override;
};

#endif //SYM_HORIZONTAL_MENU