#ifndef SYM_CLIP_REGION
#define SYM_CLIP_REGION

class RegionSet;
#include "../Vector/Vector.h"
#include "../Color.h"


class ClipRegion
{
    Vector position;
    Vector size;
    Color  color;

public:
    ClipRegion(Vector position, Vector size, Color color = Color(255, 255, 255));

    Vector GetSize()     const;
    Vector GetPosition() const;
    Color  GetColor()    const;

    void Dump();

    friend ClipRegion operator&&(ClipRegion a, ClipRegion b);
    friend RegionSet  operator||(ClipRegion a, ClipRegion b);
    friend RegionSet  operator- (ClipRegion a, ClipRegion b);
    friend bool       operator==(ClipRegion a, ClipRegion b);
};

const ClipRegion kNullClipReg = ClipRegion(Vector(0, 0), 
                                           Vector(0, 0), 
                                           Color(0, 0, 0, 0));

ClipRegion operator&&(ClipRegion a, ClipRegion b);
RegionSet  operator||(ClipRegion a, ClipRegion b);
RegionSet  operator- (ClipRegion a, ClipRegion b);
bool       operator==(ClipRegion a, ClipRegion b);

#endif //SYM_CLIP_REGION