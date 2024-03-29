#ifndef SYM_DYNAMIC_ARRAY
#define SYM_DYNAMIC_ARRAY

#include <stdlib.h>
#include <iostream>

template <class T>
class DynArray
{
    int length;
    int capacity;
    T*  array;

public :
    DynArray();
    DynArray(size_t _length);
    DynArray(const DynArray<T> &a);
    DynArray<T>& operator=(const DynArray<T> &a);
    ~DynArray();

    int GetLength()   const { return length;   }
    int GetCapacity() const { return capacity; }
    T*  GetArray()    const { return array;    }

    T& operator[](int index)
    { return array[index]; };

    const T& operator[](int index) const
    { return array[index]; };

    void PushBack(T elem);
    void Insert(T elem, int pos);
    void Remove(int pos);

    void PopBack()
    { if (length > 0) length--; };

    void Clear()
    { length = 0; }
};

template <class T>
DynArray<T>::DynArray() :
length   (0),
capacity (0),
array    (nullptr)
{}

template <class T>
DynArray<T>::DynArray(size_t _length) :
length   ((int)_length),
capacity ((int)_length),
array    (new T[_length + 1])
{}

template <class T>
DynArray<T>::DynArray(const DynArray<T> &a)
{
    length   = a.length;
    capacity = a.capacity;
    array    = new T[capacity];

    for (int i = 0; i < length; i++)
        array[i] = a[i];
};

template <class T>
DynArray<T>::~DynArray()
{
    length   = 0;
    capacity = 0;
    
    delete[] array;
    array = nullptr;
};

template <class T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T> &a)
{
    delete[] array;

    length   = a.length;
    capacity = a.capacity;
    array    = new T[capacity];
    for (int i = 0; i < length; i++)
        array[i] = a[i];

    return *this;
}

template <class T>
void DynArray<T>::PushBack(T elem)
{
    if (capacity <= length)
    {
        capacity = capacity * 2 + 1;
        if (array == nullptr)
            array = new T[capacity];
        else
        {
            T* new_array = new T[capacity];
            for (int i = 0; i < length; i++)
                new_array[i] = array[i];
            delete[] array;

            array = new_array;
        }
    }
    
    array[length] = elem;
    length++;
}

template <class T>
void DynArray<T>::Insert(T elem, int pos)
{
    if (pos < 0 || pos > length)
        return;
    if (pos == length)
    {
        PushBack(elem);
        return;
    }

    T last_one = array[length - 1];
    PushBack(last_one);
        
    for (int i = length - 1; i > pos; i--)
        array[i] = array[i - 1];
    array[pos] = elem;
}

template <class T>
void DynArray<T>::Remove(int pos)
{
    if (pos < 0 || pos >= length)
        return;
        
    for (int i = pos; i < length - 1; i++)
        array[i] = array[i + 1];
    PopBack();
}

#endif  //SYM_DYNAMIC_ARRAY