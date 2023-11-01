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
    Widget* main_button;
    bool    expanded;
    bool    static_menu;
    Vector  expanded_size;
    Vector  collapsed_size;

public:
    
    Menu(Button* button, bool static_menu);

    void ChangeExpandedStatus()
    {
        expanded = !expanded;

        if (!static_menu)
        {
            if (expanded)
            {
                size = expanded_size;
                UpdateRegionSet();
                for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
                    sub_widgets[i].val->SetAvailable(true);                
            }
            else
            {
                size = collapsed_size;
                UpdateRegionSet();
                for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
                    sub_widgets[i].val->SetAvailable(false);
                
                main_button->SetAvailable(true);
            }

            UpdateRegionSet();
        }
    }

    virtual void AddObject(Widget* new_widget)     override;
            void Render(RenderTarget* rt)          override; 
            bool OnMouseMove(MouseCondition mouse) override;
};

#endif //SYM_BUTTON_MANAGER