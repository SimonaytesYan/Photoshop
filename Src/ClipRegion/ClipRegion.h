#ifndef SYM_CLIP_REGION
#define SYM_CLIP_REGION

class RegionSet;
#include "../Vector/Vector.h"
#include "../Color.h"


class ClipRegion
{
    double x0;
    double y0;
    double x1;
    double y1;
    
    bool   nulled;
public:
    ClipRegion(double x0, double y0, double x1, double y1);
    ClipRegion(Vector position, Vector size, bool nulled = false);

    Vector GetSize()     const;
    Vector GetPosition() const;
    Color  GetColor()    const;

    void Dump() const;

    friend ClipRegion operator&&(ClipRegion a, ClipRegion b);
    friend RegionSet  operator||(ClipRegion a, ClipRegion b);
    friend RegionSet  operator- (ClipRegion a, ClipRegion b);
    friend bool       operator==(ClipRegion a, ClipRegion b);
};

const ClipRegion kNullClipReg = ClipRegion(Vector(0, 0), 
                                           Vector(0, 0), 
                                           true);

ClipRegion operator&&(ClipRegion a, ClipRegion b);
RegionSet  operator||(ClipRegion a, ClipRegion b);
RegionSet  operator- (ClipRegion a, ClipRegion b);
bool       operator==(ClipRegion a, ClipRegion b);

#endif //SYM_CLIP_REGION