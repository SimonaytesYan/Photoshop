#ifndef SYM_USEFUL
#define SYM_USEFUL

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

#endif //SYM_USEFUL