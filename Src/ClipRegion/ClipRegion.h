#ifndef SYM_CLIP_REGION
#define SYM_CLIP_REGION

class RegionSet;
#include "../Vec2/Vec2.h"
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
    ClipRegion(Vec2 position, Vec2 size, bool nulled = false);
    ClipRegion(const ClipRegion& a);

    Vec2 GetSize()     const;
    Vec2 GetPosition() const;
    Color  GetColor()    const;

    bool InsideP(Vec2 v) const;

    void Dump() const;

    friend ClipRegion operator&&(ClipRegion a, ClipRegion b);
    friend RegionSet  operator||(ClipRegion a, ClipRegion b);
    friend RegionSet  operator- (ClipRegion a, ClipRegion b);
    friend bool       operator==(ClipRegion a, ClipRegion b);
};

const ClipRegion kNullClipReg = ClipRegion(Vec2(0, 0), 
                                           Vec2(0, 0), 
                                           true);

ClipRegion operator&&(ClipRegion a, ClipRegion b);
RegionSet  operator||(ClipRegion a, ClipRegion b);
RegionSet  operator- (ClipRegion a, ClipRegion b);
bool       operator==(ClipRegion a, ClipRegion b);

#endif //SYM_CLIP_REGION