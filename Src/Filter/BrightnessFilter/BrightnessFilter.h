#ifndef SYM_BRIGHTNESS_FILTER
#define SYM_BRIGHTNESS_FILTER

#include "../Filter.h"

class BrightnessFilter : public Filter
{
    double brightness;

public:
    BrightnessFilter(double _brightness = 10)
    {
        param_names.data    = new const char*[1];
        param_names.data[0] = "brightness";
        param_names.size    = 1;

        brightness = _brightness;
    }

    plugin::Array<const char*> getParamNames() const override;

    void apply    (plugin::RenderTargetI* rt)    override;
    void setParams(plugin::Array<double> params) override;
};

#endif //SYM_BRIGHTNESS_FILTER