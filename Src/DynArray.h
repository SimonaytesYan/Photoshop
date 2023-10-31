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
    DynArray(size_t _length)
    {
        length   = _length;
        capacity = _length;
        array    = (T*)calloc(capacity+1, sizeof(T));
    };

    DynArray(const DynArray<T> &a)
    {
        length   = a.length;
        capacity = a.capacity;
        array    = (T*)calloc(capacity, sizeof(T));
        for (int i = 0; i < length; i++)
            new(array + i) T(a[i]);
    };

    DynArray<T>& operator=(const DynArray<T> &a)
    {
        for (int i = 0; i < capacity; i++)
            delete(array + i);
        free(array);

        length   = a.length;
        capacity = a.capacity;
        array    = (T*)calloc(capacity, sizeof(T));
        for (int i = 0; i < length; i++)
            new(array + i) T(a[i]);

        return *this;
    }

    ~DynArray()
    {
        length   = 0;
        capacity = 0;
        for (int i = 0; i < capacity; i++)
            delete(array + i);
        free(array);
    };

    int GetLength()   const { return length;   };
    int GetCapacity() const { return capacity; };
    T*  GetArray()    const { return array; };

    T& operator[](int index)
    { return array[index]; };

    const T& operator[](int index) const
    { return array[index]; };

    void PushBack(T elem)
    {
        if (capacity <= length)
        {
            capacity = capacity * 2 + 1;
            if (array == nullptr)
                array = (T*)calloc(capacity, sizeof(T));
            else
                array = (T*)realloc(array, capacity * sizeof(T));
        }
        
        array[length] = elem;
        length++;
    };

    void Insert(T elem, int pos)
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
    };

    void Remove(int pos)
    {
        if (pos < 0 || pos >= length)
            return;
        
        for (int i = pos; i < length - 1; i++)
            array[i] = array[i + 1];
        PopBack();
    };

    void PopBack()
    {
        if (length > 0)
            length--;
    };

    void Clear()
    {
        length = 0;
    }
};

#endif  //SYM_DYNAMIC_ARRAY