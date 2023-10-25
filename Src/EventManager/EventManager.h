#ifndef SYM_EVENT_MANAGER
#define SYM_EVENT_MANAGER

#include "../EventProcessable.h"
#include "../Event.h"
#include "../List.h"

class EventManager : EventProcessable
{
    List<EventProcessable*> objects;

    u_int8_t min_priority[EVENTS_NUMBER];
};

#endif //SYM_EVENT_MANAGER