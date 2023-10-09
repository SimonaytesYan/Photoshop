#include "RegionSet.h"
#include "../ClipRegion/ClipRegion.h"

void RegionSet::AddRegion(ClipRegion region)
{
    data.PushBack(region);
}

void RegionSet::Dump()
{
    for (int i = 0; i < data.GetLength(); i++)
    {
        data[i].Dump();
    }
}

ClipRegion RegionSet::operator[](const int index) const
{
    return data[index];
}

RegionSet& RegionSet::operator-=(const RegionSet& b)
{
    RegionSet result;

    int i = 0;
    int j = 0;
    int b_len = b.data.GetLength();
    for (i = 0; i < data.GetLength(); i++)
    {
        #ifdef DEBUG
            printf("i = %d\n", i);
        #endif
        for (j = 0; j < b_len; j++)
        {
            #ifdef DEBUG
                printf("j = %d\n", j);
            #endif
            RegionSet res = (data[i]) - (b.data[j]);

            if (res.GetLength() > 0 && !(res.data[0] == data[i]))
            {
                #ifdef DEBUG
                    printf("res = \n");
                    res.Dump();
                #endif

                data[i] = res.data[res.data.GetLength() - 1];
                for (int k = 0; k < res.data.GetLength() - 1; k++)
                    AddRegion(res.data[k]);
                i = -1;
                j = 0;

                break;
            }
        }
    }

    return *this;
}
