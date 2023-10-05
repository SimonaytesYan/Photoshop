#ifndef SYM_REGION_SET
#define SYM_REGION_SET

#include "../List.h"
class ClipRegion;
#include "../ClipRegion/ClipRegion.h"

class RegionSet
{
    List<ClipRegion*> data;

public:
    RegionSet();

    void AddRegion(ClipRegion* region);
};

#endif //SYM_REGION_SET