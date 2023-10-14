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

void RegionSet::Clear()
{
    data.Clear();
}

RegionSet::~RegionSet()
{
}

void RegionSet::AddRegion(ClipRegion region)
{
    data.PushBack(region);
}

void RegionSet::ChangeElem(size_t index, ClipRegion region)
{
    data[index] = region;
}

void RegionSet::Dump() const
{
    if (data.GetLength() == 0)
        printf("{reg set in empty}\n");
    for (int i = 0; i < data.GetLength(); i++)
    {
        data[i].Dump();
    }
}

ClipRegion RegionSet::operator[](const int index) const
{
    return data[index];
}

ClipRegion& RegionSet::operator[](const int index)
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

            if (i_y0 == j_y0 && i_y1 == j_y1)
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

    for (int i = 0; i < data.GetLength(); i++)
    {
        if (data[i] == kNullClipReg)
        {   
            Swap(&data[i], &data[data.GetLength() - 1]);
            data.PopBack();
            i--;
        }
    }
}

RegionSet& RegionSet::operator=(const RegionSet& b)
{
    data = b.data;

    return *this;
}

RegionSet& RegionSet::operator&=(const RegionSet& b)
{
    RegionSet tmp = *this;
    tmp   -= b;             //tmp = this - b
    *this -= tmp;           //this = this - (this - other)

    //UnitSet();

    return *this;
}

RegionSet& RegionSet::operator-=(const RegionSet& b)
{
    RegionSet result;

    int b_len = b.data.GetLength();

    bool add_regions = true;
    while (add_regions)
    {
        add_regions = false;
    
        for (int i = 0; i < data.GetLength(); i++)
        {
            if (data[i] == kNullClipReg)
                continue;
            for (int j = 0; j < b_len; j++)
            {
                RegionSet res = (data[i]) - (b[j]);

                if (res.GetLength() > 0 && !(res[0] == data[i]))
                {
                    data[i] = res[res.GetLength() - 1];
                    for (int k = 0; k < res.GetLength() - 1; k++)
                        AddRegion(res[k]);
                    
                    add_regions = true;
                    break;
                }
                if (res.GetLength() == 0)
                    data[i] = kNullClipReg;
            }
            if (add_regions)
                break;
        }
    }

    for (int i = 0; i < data.GetLength(); i++)
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


RegionSet& RegionSet::operator+=(const RegionSet& b) {
    *this -= b;

    for (int i = 0; i < b.data.GetLength(); i++) {
        data.PushBack(b.data[i]);
    }

    //UnitSet();

    return *this;
}
