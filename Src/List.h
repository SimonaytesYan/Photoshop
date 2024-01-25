#ifndef SYM_LIST
#define SYM_LIST

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

const int ResizeCoef = 2;

template <class T>
struct ListElem 
{
    T   val;
    int next = -1;
    int prev = -1;

    ListElem() :
    val  (T()),
    next (0),
    prev (0)
    { }

    ListElem& operator=(const ListElem& other) 
    { 
        val  = other.val;
        next = other.next;
        prev = other.prev;

        return *this;
    }
};

template <class T>
struct List 
{
    size_t       size     = 0;
    size_t       capacity = 0;
    ListElem<T>* data     = nullptr;
    int          free_i   = -1;

    List(int capacity);
    List(const List<T>& other);
    List<T>& operator=(const List<T>& other);
    ~List();

    int  Insert    (T value, int after_which);
    int  Remove    (int index);
    int  Iterate   (int index);
    int  Deterate  (int index);
    int  Begin     () const;
    int  End       () const;
    int  FindFree  (int* index);
    int  ResizeUp  (int new_capacity);
    int  PushFront (T value);
    int  PushBack  (T value);
    void PopFront  ();
    void PopBack ();

    void Clear();
    void Dump();
    void AllDump();

    ListElem<T>& operator[](int index);
};

template <class T>
ListElem<T>& List<T>::operator[](int index)
{
    return data[index];
}

template <class T>
int List<T>::Iterate(int index)
{
    if (index < 0 || (size_t)(index) > capacity)
        return -1;

    if (data[index].next != 0)
        return data[index].next;
    // else
    return -1;
}

template <class T>
int List<T>::Deterate(int index)
{
    if (index < 0 || (size_t)(index) > capacity)
        return -1;

    if (data[index].prev != 0)
        return data[index].prev;
    // else
    return -1;
}

template <class T>
int List<T>::Begin() const
{
    if (capacity >= 1)
        return data[0].next;
    return -1;
}

template <class T>
int List<T>::End() const
{
    if (capacity >= 1)
        return data[0].prev;
    return -1;
}

template <class T>
List<T>::List(int _capacity)
{
    size     = 0;
    capacity = _capacity;
    free_i     = -1;

    data     = new ListElem<T>[capacity + 1];
    if (data != nullptr)
    {
        for(int i = capacity; i >= 1; i--)
        {            
            data[i].next = -1;
            data[i].prev = free_i;
            free_i  = i;
        }
    }
}


template <class T>
List<T>::List(const List<T>& other)
{
    size     = other.size;
    capacity = other.capacity;
    free_i   = other.free_i;
    data     = new ListElem<T>[capacity + 1];

    for (int i = capacity; i >= 1; i--)
        data[i] = other.data[i];
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other)
{
    delete[] data;

    size     = other.size;
    capacity = other.capacity;
    free_i   = other.free_i;
    data     = new ListElem<T>[capacity + 1];

    for (int i = 0; i <= capacity; i++)
        data[i] = other.data[i];
    
    return *this;
}

template <class T>
List<T>::~List()
{
    capacity  = -1;
    size      = -1;
    free_i    = -1;

    delete[] data;
}

template <class T>
void List<T>::Clear()
{
    size   = 0;
    free_i = -1;
    data[0].next = 0;
    data[0].prev = 0;

    for (int i = capacity; i >= 1; i--)
    {
        data[i].next = -1;
        data[i].prev = free_i;
        free_i  = i;
    }
}

// Dump only filled in part of list
template <class T>
void List<T>::Dump()
{
    fprintf(stderr, "\n{------------------------\n");
    for (int i = Begin(); i != -1; i = Iterate(i))
        fprintf(stderr, "[prev %d] val %p [next %d]\n", data[i].prev, data[i].val, data[i].next);
    fprintf(stderr, "------------------------}\n\n");
}

// Dump all information about list
template <class T>
void List<T>::AllDump()
{
    fprintf(stderr, "\n{------------------------\n");
    fprintf(stderr, "size     = %d\n",   size);
    fprintf(stderr, "capacity = %d\n",   capacity);
    fprintf(stderr, "data     = %p\n",   data);
    fprintf(stderr, "free_i   = %d\n\n", free_i);
    for (int i = 0; i <= capacity; i++)
        fprintf(stderr, "[prev %d] val %p [next %d]\n", data[i].prev, data[i].val, data[i].next);
    fprintf(stderr, "------------------------}\n\n");
}

template <class T>
int List<T>::FindFree(int* index)
{
    *index = free_i;
    free_i = data[free_i].prev;

    return 0;
}

template <class T>
int List<T>::Remove(int index)
{
    int next_ind = data[index].next;
    int prev_ind = data[index].prev;

    if (prev_ind != -1)
        data[prev_ind].next = next_ind;
    if (next_ind != -1)
        data[next_ind].prev = prev_ind;

    data[index].prev = free_i;
    data[index].next = -1;

    free_i = index;
 
    size--;

    return 0;
}

template <class T>
int List<T>::ResizeUp(int new_capacity)
{
    ListElem<T>* new_data = new ListElem<T>[new_capacity + 1];
    for (int i = 0; i <= capacity; i++)
        new_data[i] = data[i];
    
    delete[] data;
    data = new_data;

    for(int i = new_capacity; i >= capacity + 1; i--)
    {
        data[i].next = -1;
        data[i].prev = free_i;
        free_i = i;
    }
    
    capacity = new_capacity;

    return 0;
}

template <class T>
int ResizeIfNeed(List<T> *list)
{
    if (list->capacity == list->size)
    {
        int new_capacity = 0;
        if (list->capacity == 0)
            new_capacity = 2;
        else
            new_capacity = list->capacity * ResizeCoef;
        list->ResizeUp(new_capacity);
    }

    return 0;
}

template <class T>
int List<T>::Insert(T value, int after_which) 
{
    AllDump();

    ResizeIfNeed(this);

    AllDump();

    int index = -1;
    FindFree(&index);
    
    ListElem<T>* new_elem = &data[index];
    new_elem->val = value;
    
    int next       = data[after_which].next;
    new_elem->next = next;
    new_elem->prev = after_which;

    data[next].prev        = index; 
    data[after_which].next = index;

    size++;

    return 0;
}

template <class T>
int List<T>::PushFront(T value) 
{
    return Insert(value, 0);
}

template <class T>
int List<T>::PushBack(T value)
{
    int after_which = End();
    if (after_which == -1)
        after_which = 0;
    return Insert(value, after_which);    
}

template <class T>
void List<T>::PopFront()
{
    int first = Begin();
    if (first != -1)
        Remove(first);
}

template <class T>
void List<T>::PopBack()
{
    int last = End();
    if (last != -1)
        Remove(last);

    abort();
}

#endif  //SYM_LIST
