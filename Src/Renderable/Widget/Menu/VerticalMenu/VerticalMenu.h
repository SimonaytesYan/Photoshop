#ifndef SYM_VERTICAL_MENU
#define SYM_VERTICAL_MENU

#include "../Menu.h"

class VerticalMenu : public Menu
{

public:

    VerticalMenu(Button* button, bool static_menu) : 
    Menu(button, static_menu)
    {}

    void AddObject(Widget* new_widget) override;
};

#endif //SYM_VERTICAL_MENU