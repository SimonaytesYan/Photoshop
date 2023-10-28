#ifndef SYM_MODAL_WINDOW
#define SYM_MODAL_WINDOW

#include "Window.h"
#include "../../../EventManager/EventManager.h"

class ModalWindow : public Window
{
    EventManager* event_manager;

public:
    ModalWindow(Vector _position, Vector _size, char* _header, 
                EventManager* _event_manager) :
    Window(_position, _size, _header),
    event_manager (_event_manager)
    {
        priority = 1;
        event_manager->AddObject(this);

        DynArray<Events> events(5);
        events[0] = MOUSE_MOVE;
        events[1] = MOUSE_PRESS;
        events[2] = MOUSE_RELEASE;
        events[3] = KEY_RELEASE;
        events[4] = KEY_PRESS;

        event_manager->ChangePriority(events, 1);
    }

    ~ModalWindow()
    {
        event_manager->ResetPriorities();
        event_manager->RemoveObject(this);
    }
};

#endif //SYM_MODAL_WINDOW