#ifndef SYM_CLIP_REGION
#define SYM_CLIP_REGION

class RegionSet;
#include "../Standart/Standart.h"
#include "../Color.h"


class ClipRegion
{    
    bool   nulled;

public:
    double x0;
    double y0;
    double x1;
    double y1;

    ClipRegion();
    ClipRegion(double x0, double y0, double x1, double y1);
    ClipRegion(plugin::Vec2 position, plugin::Vec2 size, bool nulled = false);
    ClipRegion(const ClipRegion& a);

    plugin::Vec2 getSize()     const;
    plugin::Vec2 getPosition() const;
    plugin::Color  GetColor()    const;

    bool InsideP(plugin::Vec2 v) const;

    void Dump() const;

    friend ClipRegion operator&&(ClipRegion a, ClipRegion b);
    friend RegionSet  operator||(ClipRegion a, ClipRegion b);
    friend RegionSet  operator- (ClipRegion a, ClipRegion b);
    friend bool       operator==(ClipRegion a, ClipRegion b);
};

const ClipRegion kNullClipReg = ClipRegion(plugin::Vec2(0, 0), 
                                           plugin::Vec2(0, 0), 
                                           true);

ClipRegion operator&&(ClipRegion a, ClipRegion b);
RegionSet  operator||(ClipRegion a, ClipRegion b);
RegionSet  operator- (ClipRegion a, ClipRegion b);
bool       operator==(ClipRegion a, ClipRegion b);

#endif //SYM_CLIP_REGION