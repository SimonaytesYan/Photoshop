#ifndef SYM_EVENT_MANAGER_I
#define SYM_EVENT_MANAGER_I

#include "Standart.h"

namespace plugin
{
    enum class EventType 
    {
        MousePress,
        MouseRelease,
        MouseMove,
        KeyPress,
        KeyRelease,
        Clock,
    	NumOfEvents,
    };

    struct EventManagerI 
    {
        virtual void registerObject(EventProcessableI *object)   = 0;

        // 0 минимальный, ивенты приходят только объектам с их priority >= установленной по этому типу
        // 0 -- default
        virtual void setPriority(EventType event, uint8_t priority)    = 0;
        virtual void unregisterObject(EventProcessableI *object) = 0;
    };
}

#endif //SYM_EVENT_MANAGER_I
