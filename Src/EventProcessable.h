#ifndef SYM_EVENT_PROCESSABLE
#define SYM_EVENT_PROCESSABLE

#include "Keys.h"
#include "Standart/EventProcessableI.h"

class EventProcessable : public EventProcessableI
{
protected :
    u_int8_t priority;

public : 

    u_int8_t getPriority() override
    { return priority; }

    EventProcessable(int _priority) :
    priority (_priority)
    { priority = _priority; }

    ~EventProcessable()
    { priority = 0; }
};

#endif //SYM_EVENT_PROCESSABLE