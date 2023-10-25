#ifndef SYM_EVENT_MANAGER
#define SYM_EVENT_MANAGER

#include "../EventProcessable.h"
#include "../Event.h"
#include "../DynArray.h"
#include "../Useful.h"
#include "../List.h"

const u_int8_t kDefaultPriority = 0;

class EventManager : EventProcessable
{
    List<EventProcessable*> objects;
    u_int8_t min_priority[EVENTS_NUMBER];

public:
    EventManager() :
    EventProcessable(0),
    objects (List<EventProcessable*>(0))
    {
        for (int i = 0; i < EVENTS_NUMBER; i++)
            min_priority[i] = kDefaultPriority;
    }

    void ChangePriority(DynArray<Events> events, int new_min_priority);
    void ResetPriorities();

    void AddObject   (EventProcessable* obj);
    void RemoveObject(EventProcessable* obj);

    bool OnKeyPress    (Key key)              override;
    bool OnKeyRelease  (Key key)              override;
    bool OnMousePress  (MouseCondition mouse) override;
    bool OnMouseRelease(MouseCondition mouse) override;
    bool OnMouseMove   (MouseCondition mouse) override;
    bool OnClock       (u_int64_t delta)      override;
};

#endif //SYM_EVENT_MANAGER