#ifndef SYM_EVENT_PROCESSABLE
#define SYM_EVENT_PROCESSABLE

#include "Keys.h"

class EventProcessable
{
protected :
    u_int8_t priority;

public :
    virtual bool OnKeyPress    (Key key)              = 0;
    virtual bool OnKeyRelease  (Key key)              = 0;
    virtual bool OnMousePress  (MouseCondition mouse) = 0;
    virtual bool OnMouseRelease(MouseCondition mouse) = 0;
    virtual bool OnMouseMove   (MouseCondition mouse) = 0;
    virtual bool OnClock       (u_int64_t delta)      = 0;

    u_int8_t GetPriority()
    { return priority; }

    EventProcessable(int _priority) :
    priority (_priority)
    { priority = _priority; }

    ~EventProcessable()
    { priority = 0; }
};

#endif //SYM_EVENT_PROCESSABLE