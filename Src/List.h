#ifndef SYM_LIST
#define SYM_LIST

#include <stdlib.h>
#include <time.h>

const int ResizeCoef = 2;

template <class T>
struct ListElem 
{
    T   val  = 0;
    int next = -1;
    int prev = -1;
};

template <class T>
struct List 
{
    size_t       size     = 0;
    size_t       capacity = 0;
    ListElem<T>* data     = nullptr;
    int          free_i   = -1;

    List(int _capacity);
    ~List();
    int  Insert    (T value, int after_which);
    int  Remove    (int index);
    int  Iterate   (int index);
    int  Deterate  (int index);
    int  Begin     ();
    int  End       ();
    int  FindFree  (int* index);
    int  ResizeUp  (int new_capacity);
    int  PushFront (T value);
    int  PushBack  (T value);
    void PopFront  ();
    void PopBack ();

    void Clear();

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

    return -1;
}

template <class T>
int List<T>::Deterate(int index)
{
    if (index < 0 || (size_t)(index) > capacity)
        return -1;

    if (data[index].prev != 0)
        return data[index].prev;

    return -1;
}

template <class T>
int List<T>::Begin()
{
    if (capacity >= 1)
        return data[0].next;
    return -1;
}

template <class T>
int List<T>::End()
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

    data     = (ListElem<T>*)calloc(capacity + 1, sizeof(ListElem<T>));
    if (data != nullptr)
        for(int i = capacity; i >= 1; i--)
        {            
            data[i].next = -1;
            data[i].prev = free_i;
            free_i  = i;
        }
}

template <class T>
List<T>::~List()
{
    capacity  = -1;
    size      = -1;
    free_i    = -1;

    free(data);
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

    data[prev_ind].next = next_ind;
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
    data = (ListElem<T>*)realloc(data, sizeof(ListElem<T>)*(new_capacity + 1));

    if (data == nullptr)
        return -1;

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
    ResizeIfNeed(this);

    int index = 0;
    int free_elem_index = -1;
    FindFree(&free_elem_index);

    index = free_elem_index;

    int tail = 0;
    tail = End();
    
    ListElem<T>* new_elem = &data[free_elem_index];
    new_elem->val = value;
    
    int next       = data[after_which].next;
    new_elem->next = next;
    new_elem->prev = after_which;

    data[next].prev        = free_elem_index; 
    data[after_which].next = free_elem_index;

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
