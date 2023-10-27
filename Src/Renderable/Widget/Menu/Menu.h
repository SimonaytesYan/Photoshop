#ifndef SYM_BUTTON_MANAGER
#define SYM_BUTTON_MANAGER

#include <SFML/Graphics.hpp>

#include "../Widget.h"
#include "../Button/Button.h"

void CallChangeExpandedStatus(void* _args);

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
    bool          expanded;
    bool          static_menu;
    List<Widget*> expanded_objects;
    List<Widget*> collapsed_objects; 

public:
    
    Menu(Button* button, bool _static_menu);

    void ChangeExpandedStatus()
    {
        expanded = !expanded;
    }

    virtual void AddObject   (Widget* new_widget)          override;
            void Render      (RenderTarget* render_target) override;
};

#endif //SYM_BUTTON_MANAGER