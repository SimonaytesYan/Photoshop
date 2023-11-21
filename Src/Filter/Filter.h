#ifndef SYM_FILTER
#define SYM_FILTER

#include "../RenderTarget/RenderTarget.h"
#include "../DynArray.h"
#include "../Standart/FilterI.h"

class Filter : public plugin::FilterI
{

public:
    virtual DynArray<const char*> GetParamNames()   = 0;
    
    virtual void Apply    (RenderTarget& rt)               = 0;
    virtual void SetParams(const DynArray<double>& params) = 0;
};

#endif //SYM_FILTER