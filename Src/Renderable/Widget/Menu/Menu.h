#ifndef SYM_BUTTON_MANAGER
#define SYM_BUTTON_MANAGER

#include <SFML/Graphics.hpp>

#include "../Widget.h"
#include "../Button/Button.h"

//
// First element in Menu.objects is main button, 
// press or it expand or collapse menu. 
//
// This button didn`t expand or collapse menu if static_menu is true.
//
// Appropriate on_press function set by Menu constructor 
// (only if static_menu - false) 
//
//
class Menu : public Widget
{

protected:
    Widget* main_button;
    bool    expanded;
    bool    static_menu;

public:
    
    Menu(Button* button, bool static_menu);
    Menu(Widget* widget);

    void ChangeExpandedStatus();

    virtual void AddObject  (Widget* new_widget)   override;
            bool OnMouseMove(MouseContext mouse) override;
            bool InsideP    (Vec2 v)             override;
            void UpdateOwnDefaultRegionSet()       override;
};

#endif //SYM_BUTTON_MANAGER