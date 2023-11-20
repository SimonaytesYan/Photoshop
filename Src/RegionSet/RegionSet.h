#ifndef SYM_REGION_SET
#define SYM_REGION_SET

#include "../Vec2/Vec2.h"
#include "../DynArray.h"
class ClipRegion;

class RegionSet
{
    DynArray<ClipRegion> data;

public:
    RegionSet() :
    data (DynArray<ClipRegion>(0))
    {}

    RegionSet(const RegionSet& b) :
    data (DynArray<ClipRegion>(b.data))
    {}

    ~RegionSet();

    void UnitSet   ();
    void AddRegion (ClipRegion region);
    void ChangeElem(size_t index, ClipRegion region);
    void Clear     ();
    bool InsideP   (plugin::Vec2 v) const;

    RegionSet&  operator= (const RegionSet& b);
    RegionSet&  operator-=(const RegionSet& b);
    RegionSet&  operator+=(const RegionSet& b);
    RegionSet&  operator&=(const RegionSet& b);
    ClipRegion& operator[](const int index);
    ClipRegion  operator[](const int index) const;


    int GetLength() const
    { return data.GetLength(); };

    void Dump() const;
};

#endif //SYM_REGION_SET