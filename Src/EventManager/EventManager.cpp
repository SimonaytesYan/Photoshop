#include "EventManager.h"

bool EventManager::OnKeyPress(Key key)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->GetPriority() >= min_priority[KEY_PRESS])
            objects[i].val->OnKeyPress(key);
    }

    return true;
}

bool EventManager::OnKeyRelease(Key key)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->GetPriority() >= min_priority[KEY_RELEASE])
            objects[i].val->OnKeyRelease(key);
    }

    return true;
}

bool EventManager::OnMousePress(MouseContext mouse)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->GetPriority() >= min_priority[MOUSE_PRESS])
            objects[i].val->OnMousePress(mouse);
    }

    return true;
}

bool EventManager::OnMouseRelease(MouseContext mouse)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->GetPriority() >= min_priority[MOUSE_RELEASE])
            objects[i].val->OnMouseRelease(mouse);
    }

    return true;
}

bool EventManager::OnMouseMove(MouseContext mouse)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->GetPriority() >= min_priority[MOUSE_MOVE])
            objects[i].val->OnMouseMove(mouse);
    }

    return true;
}

bool EventManager::OnClock(u_int64_t delta)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val->GetPriority() >= min_priority[ON_CLOCK])
            objects[i].val->OnClock(delta);
    }

    return true;
}

void EventManager::ChangePriority(DynArray<Events> events, int new_min_priority)
{
    for (int i = 0; i < events.GetLength(); i++)
        min_priority[events[i]] = new_min_priority;
}

void EventManager::ResetPriorities()
{
    for (int i = 0; i < EVENTS_NUMBER; i++)
        min_priority[i] = kDefaultPriority;
}

void EventManager::AddObject(EventProcessable* obj)
{
    objects.PushBack(obj);
}


void EventManager::RemoveObject(EventProcessable* obj)
{
    for (int i = objects.Begin(); i != -1; i = objects.Iterate(i))
    {
        if (objects[i].val == obj)
            objects.Remove(i);
    }
}
