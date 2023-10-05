#include "RegionSet.h"

void RegionSet::AddRegion(ClipRegion* region)
{
    data.PushFront(region);
}
