#ifndef SYM_EVENT_PROCESSABLE
#define SYM_EVENT_PROCESSABLE

#include "Standart/Standart.h"

class EventProcessable : public plugin::EventProcessableI
{
protected :
    uint8_t priority;

public : 
    EventProcessable() :
    priority (0)
    { }

    uint8_t getPriority() override
    { return priority; }

    EventProcessable(int _priority) :
    priority (_priority)
    { priority = _priority; }

    ~EventProcessable()
    { priority = 0; }
};

#endif //SYM_EVENT_PROCESSABLE