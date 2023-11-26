#ifndef SYM_EVENT_MANAGER
#define SYM_EVENT_MANAGER

#include "../Standart/Standart.h"
#include "../EventProcessable.h"
#include "../Event.h"
#include "../DynArray.h"
#include "../Useful.h"
#include "../List.h"


const uint8_t kDefaultPriority = 0;

class EventManager : EventProcessable, plugin::EventManagerI
{
    List<plugin::EventProcessableI*> objects;
    uint8_t min_priority[EVENTS_NUMBER];

public:
    EventManager() :
    EventProcessable(0),
    objects (List<plugin::EventProcessableI*>(0))
    {
        for (int i = 0; i < EVENTS_NUMBER; i++)
            min_priority[i] = kDefaultPriority;
    }

    void ChangePriorities(DynArray<Events> events, int new_min_priority);
    void ResetPriorities();

    void setPriority(plugin::EventType event, uint8_t priority) override;

    void registerObject  (plugin::EventProcessableI* obj) override;
    void unregisterObject(plugin::EventProcessableI* obj) override;

    bool onKeyboardPress  (plugin::KeyboardContext key) override;
    bool onKeyboardRelease(plugin::KeyboardContext key) override;
    bool onMousePress     (plugin::MouseContext mouse)  override;
    bool onMouseRelease   (plugin::MouseContext mouse)  override;
    bool onMouseMove      (plugin::MouseContext mouse)  override;
    bool onClock          (u_int64_t delta)     override;
};

#endif //SYM_EVENT_MANAGER