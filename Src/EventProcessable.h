#ifndef SYM_EVENT_PROCESSABLE
#define SYM_EVENT_PROCESSABLE

#include "Keys.h"
#include "Standart/EventProcessableI.h"

class EventProcessable
{
protected :
    u_int8_t priority;

public :
    virtual bool OnKeyPress    (KeyboardContext key)              = 0;
    virtual bool OnKeyRelease  (KeyboardContext key)              = 0;
    virtual bool OnMousePress  (MouseContext mouse) = 0;
    virtual bool OnMouseRelease(MouseContext mouse) = 0;
    virtual bool OnMouseMove   (MouseContext mouse) = 0;
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