#ifndef SYM_REGION_SET
#define SYM_REGION_SET

#include "../DynArray.h"
class ClipRegion;

class RegionSet
{
    DynArray<ClipRegion> data;

public:
    RegionSet() :
    data (DynArray<ClipRegion>(0))
    {};

    void UnitSet();
    void AddRegion(ClipRegion region);
    RegionSet& operator-=(const RegionSet& b);
    ClipRegion operator[](const int index) const;

    friend RegionSet operator&&(RegionSet a, RegionSet b);
    friend RegionSet operator||(RegionSet a, RegionSet b);

    int GetLength() const
    { return data.GetLength(); };

    void Dump();
};

RegionSet operator&&(RegionSet a, RegionSet b);
RegionSet operator||(RegionSet a, RegionSet b);

#endif //SYM_REGION_SET