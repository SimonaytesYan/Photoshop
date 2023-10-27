#ifndef SYM_HORIZONTAL_MENU
#define SYM_HORIZONTAL_MENU

#include "../Menu.h"

class HorizontalMenu : public Menu
{

public:

    HorizontalMenu(Button* button, bool _static_menu) : 
    Menu(button, _static_menu)
    {}

    void AddObject(Widget* new_widget) override;
};

#endif //SYM_HORIZONTAL_MENU