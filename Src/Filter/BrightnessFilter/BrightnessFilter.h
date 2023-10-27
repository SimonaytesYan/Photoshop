#ifndef SYM_BRIGHTNESS_FILTER
#define SYM_BRIGHTNESS_FILTER

#include "../Filter.h"

class BrightnessFilter : public Filter
{
    double brightness;

public:
    BrightnessFilter(double _brightness = 10)
    {
        brightness = _brightness;
    }

    DynArray<const char*> GetParamNames()                               override;
    void                  Apply        (RenderTarget& rt)               override;
    void                  SetParams    (const DynArray<double>& params) override;
};

#endif //SYM_BRIGHTNESS_FILTER