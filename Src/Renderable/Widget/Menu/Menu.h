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

    virtual void registerSubWidget       (plugin::WidgetI* new_widget) override;
            bool onMouseMove             (plugin::MouseContext mouse)  override;
            bool InsideP                 (plugin::Vec2 v)              override;
            void UpdateOwnDefaultRegionSet()                           override;
    
    Widget* getMainButton() { return main_button; };

    bool onMouseRelease   (plugin::MouseContext mouse)    override;
    bool onMousePress     (plugin::MouseContext mouse)    override;
    bool onKeyboardPress  (plugin::KeyboardContext mouse) override;
    bool onKeyboardRelease(plugin::KeyboardContext mouse) override;
    bool onClock          (size_t delta)                  override;
};

#endif //SYM_BUTTON_MANAGER