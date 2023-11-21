#ifndef SYM_BLACK_AND_WHITE_FILTER
#define SYM_BLACK_AND_WHITE_FILTER

#include "../Filter.h"

class BlackAndWhiteFilter : public Filter
{

public:
    BlackAndWhiteFilter()
    {}

    plugin::Array<const char*> getParamNames()                               override;
    void                  apply        (plugin::RenderTargetI* rt)               override;
    void                  setParams    (plugin::Array<double> params) override;
};

#endif //SYM_BRIGHTNESS_FILTER