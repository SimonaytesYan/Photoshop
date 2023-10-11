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
        array    = (T*)calloc(length+1, sizeof(T));
    };

    DynArray(const DynArray<T> &a)
    {
        length   = a.length;
        capacity = a.capacity;
        array    = (T*)calloc(length, sizeof(T));
        for (int i = 0; i < length; i++)
            new(array + i) T(a[i]);
    };

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

    T& operator[](int index)
    { return array[index]; };

    const T& operator[](int index) const
    { return array[index]; };

    void PushBack(T elem)
    {
        if (capacity <= length)
        {
            capacity = capacity * 2 + 1;
            // std::cout << "capacity " << capacity << " \n";
            array = (T*)realloc(array, capacity * sizeof(T));
            // std::cout << "resize\n";
        } else {
            // std::cout << "not resize\n";
        }

        // std::cout << "length " << length << " capacity " << capacity;
        array[length] = elem;
        //new(array + length) T(elem);
        length++;
    };

    void PopBack()
    {
        if (length > 0)
            length--;
    };
};

#endif  //SYM_DYNAMIC_ARRAY