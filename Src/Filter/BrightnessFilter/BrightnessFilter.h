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

    plugin::Array<const char*> getParamNames()                               override;
    void                  apply        (RenderTarget& rt)               override;
    void                  setParams    (plugin::Array<double> params) override;
};

#endif //SYM_BRIGHTNESS_FILTER