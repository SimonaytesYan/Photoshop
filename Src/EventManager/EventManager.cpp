#include "EventManager.h"

bool EventManager::onKeyboardPress(plugin::KeyboardContext key)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->getPriority() >= min_priority[KEY_PRESS])
            objects[i].val->onKeyboardPress(key);
    }

    return true;
}

bool EventManager::onKeyboardRelease(plugin::KeyboardContext key)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->getPriority() >= min_priority[KEY_RELEASE])
            objects[i].val->onKeyboardRelease(key);
    }

    return true;
}

bool EventManager::onMousePress(plugin::MouseContext mouse)
{
    fprintf(stderr, "press min_prior = %d\n", min_priority[MOUSE_PRESS]);
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        fprintf(stderr, "object[%d] priority = %d\n", i, objects[i].val->getPriority());
        if (objects[i].val->getPriority() >= min_priority[MOUSE_PRESS])
            objects[i].val->onMousePress(mouse);
    }

    return true;
}

bool EventManager::onMouseRelease(plugin::MouseContext mouse)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->getPriority() >= min_priority[MOUSE_RELEASE])
            objects[i].val->onMouseRelease(mouse);
    }

    return true;
}

bool EventManager::onMouseMove(plugin::MouseContext mouse)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->getPriority() >= min_priority[MOUSE_MOVE])
            objects[i].val->onMouseMove(mouse);
    }

    return true;
}

bool EventManager::onClock(u_int64_t delta)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->getPriority() >= min_priority[ON_CLOCK])
            objects[i].val->onClock(delta);
    }

    return true;
}

void EventManager::setPriority(plugin::EventType event, uint8_t priority)
{
    min_priority[(int)event] = priority;
}

void EventManager::ChangePriorities(DynArray<Events> events, int new_min_priority)
{
    for (int i = 0; i < events.GetLength(); i++)
        min_priority[events[i]] = new_min_priority;
}

void EventManager::ResetPriorities()
{
    for (int i = 0; i < EVENTS_NUMBER; i++)
        min_priority[i] = kDefaultPriority;
}
void EventManager::registerObject(plugin::EventProcessableI* obj)
{
    objects.PushBack(obj);
}

void EventManager::unregisterObject(plugin::EventProcessableI* obj)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val == obj)
            objects.Remove(i);
    }
}
