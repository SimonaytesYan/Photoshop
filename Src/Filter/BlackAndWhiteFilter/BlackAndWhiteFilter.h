#ifndef SYM_BLACK_AND_WHITE_FILTER
#define SYM_BLACK_AND_WHITE_FILTER

#include "../Filter.h"

class BlackAndWhiteFilter : public Filter
{

public:
    BlackAndWhiteFilter()
    {}

    DynArray<const char*> GetParamNames()                               override;
    void                  Apply        (RenderTarget& rt)               override;
    void                  SetParams    (const DynArray<double>& params) override;
};

#endif //SYM_BRIGHTNESS_FILTER