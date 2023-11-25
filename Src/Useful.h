#ifndef SYM_USEFUL
#define SYM_USEFUL

#include <cstdint>

#include "Color.h"

namespace plugin
{
    template<class T>
    struct Array 
    {
        uint64_t size;
        T* data;

        Array(uint64_t size = 0, T* data = nullptr) :
        size (size),
        data (data)
        {}
    };
}

template <class T1, class T2>
struct Pair 
{
    T1 first;
    T2 second;
};

static double min(double a, double b)
{
    return a < b ? a : b;
}

static double max(double a, double b)
{
    return a < b ? b : a;
}

template <class T>
static void Swap(T* a, T* b)
{
    T c = *a;
    *a = *b;
    *b = c;
}

static plugin::Color* GetC(const u_int8_t* pixels, VectorI size, VectorI index_v)
{
    int index = (index_v.y * size.x + index_v.x) * sizeof(plugin::Color);
    return (plugin::Color*)(pixels + index);
}

static double BorderPlus(double a, double b, double border)
{
    return border <= (a + b) ? border : (a + b);
}

#endif //SYM_USEFUL