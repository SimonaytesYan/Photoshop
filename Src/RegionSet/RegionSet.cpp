#include "RegionSet.h"
#include "../ClipRegion/ClipRegion.h"

//#define DEBUG

template <class T>
void Swap(T* a, T* b)
{
    T c = *a;
    *a = *b;
    *b = c;
}

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

void RegionSet::UnitSet()
{
    for (int i = 0; i < data.GetLength(); i++)
    {
        int j = i + 1;
        for (j = i + 1; j < data.GetLength(); j++)
        {   
            if (data[j] == kNullClipReg)
                continue;
            
            double i_x0 = data[i].GetPosition().GetX();
            double i_y0 = data[i].GetPosition().GetY();
            double i_x1 = (data[i].GetPosition() + data[i].GetSize()).GetX();
            double i_y1 = (data[i].GetPosition() + data[i].GetSize()).GetY();

            double j_x0 = data[j].GetPosition().GetX();
            double j_y0 = data[j].GetPosition().GetY();
            double j_x1 = (data[j].GetPosition() + data[j].GetSize()).GetX();
            double j_y1 = (data[j].GetPosition() + data[j].GetSize()).GetY();

            if (i_x0 == j_x0 && i_x1 == j_x1)
            {
                if (i_y1 == j_y0)   //j
                {                   //i
                    data[i] = ClipRegion(Vector(i_x0,        i_y0), 
                                         Vector(j_x1 - j_x0, j_y1 - i_y0));
                    data[j] = kNullClipReg;
                    j = i;
                    continue;
                }

                if (j_y1 == i_y0)   //i
                {                   //j
                    data[i] = ClipRegion(Vector(j_x0,        j_y0), 
                                         Vector(j_x1 - j_x0, i_y1 - j_y0));
                    data[j] = kNullClipReg;
                    j = i;
                    continue;
                }
            }

            if (i_y0 == j_y1 && i_y1 == j_y1)
            {
                if (i_x1 == j_x0)   //i j
                {
                    data[i] = ClipRegion(Vector(i_x0,        i_y0),
                                         Vector(j_x1 - i_x0, i_y1 - i_y0));
                    data[j] = kNullClipReg;
                    j = i;
                    continue;
                }

                if (j_x1 == i_x0)   //j i
                {
                    data[i] = ClipRegion(Vector(j_x0,        j_y0), 
                                         Vector(i_x1 - j_x0, i_y1 - i_y0));
                    data[j] = kNullClipReg;
                    j = i;
                    continue;
                }
            }
        }
    }
}

RegionSet& RegionSet::operator&=(const RegionSet& b)
{
    RegionSet tmp = *this;
    tmp   -= b;             //tmp = this - b
    *this -= tmp;           //this = this - (this - other)

    return *this;
}

RegionSet& RegionSet::operator-=(const RegionSet& b)
{
    RegionSet result;

    int i = 0;
    int j = 0;
    int b_len = b.data.GetLength();
    for (i = 0; i < data.GetLength(); i++)
    {
        if (data[i] == kNullClipReg)
            continue;
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
            else if (res.GetLength() == 0)
            {
                data[i] = kNullClipReg;
            }
        }
    }

    for (i = 0; i < data.GetLength(); i++)
    {
        if (data[i] == kNullClipReg)
        {   
            Swap(&data[i], &data[data.GetLength() - 1]);
            data.PopBack();
            i--;
        }
    }

    return *this;
}
