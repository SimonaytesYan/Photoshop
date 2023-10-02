#include "Swap.h"

template <class T>
int Swap(T* a, T* b)
{
    T c = *a;
    *a = *b;
    *b = c;
}
