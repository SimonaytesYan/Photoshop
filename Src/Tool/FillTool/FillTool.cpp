#include "FillTool.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"

const size_t  kTransNumb               = 4;
const VectorI kTransitions[kTransNumb] = {VectorI(1,  0), 
                                          VectorI(0,  1), 
                                          VectorI(-1, 0), 
                                          VectorI(0,  -1)};

Color GetC(const u_int8_t* pixels, VectorI size, VectorI index_v)
{
    int index = (index_v.y * size.x + index_v.x) * sizeof(Color);
    Color res(pixels[index],
              pixels[index + 1], 
              pixels[index + 2], 
              pixels[index + 3]);
    return res;
}

bool GoToPixelP(VectorI cur, VectorI next, 
                VectorI size, const u_int8_t* pixels, bool** visited)
{
    return 0 <= next.x && next.x < size.x &&
           0 <= next.y && next.y < size.y &&
           GetC(pixels, size, cur) == GetC(pixels, size, next) &&
           !visited[next.y][next.x];
}

void AddTransitions(DynArray<VectorI> &queue, VectorI cur,
                    const u_int8_t* pixels, VectorI size, bool** visited)
{
    for (int i = 0; i < kTransNumb; i++)
    {
        VectorI next = cur + kTransitions[i];

        if (GoToPixelP(cur, next, size, pixels, visited))
            queue.PushBack(next);
    }
}

void FillTool::PaintOnRelease(RenderTarget& data, RenderTarget& tmp, 
                              MouseCondition mouse, Color color)
{
    if (drawing)
    {
        DynArray<VectorI> queue(0);

        VectorI   size(0, 0);
        const u_int8_t* pixels = data.GetTexture().GetPixelArray(size);
        bool**    visited      = (bool**)calloc(sizeof(bool*), size.y);

        for (int i = 0; i < size.y; i++)
            visited[i] = (bool*)calloc(sizeof(bool), size.x);

        queue.PushBack(start_pos);

        while (queue.GetLength() != 0)
        {
            VectorI cur = queue[queue.GetLength() - 1];
            visited[cur.y][cur.x] = true;
            data.SetPixel(Vector(cur.x, cur.y), color);
            queue.PopBack();
            
            AddTransitions(queue, cur, pixels, size, visited);
        }

        drawing = false;

        for (int i = 0; i < size.y; i++)
            free(visited[i]);
        free(visited);
    }
}


void FillTool::PaintOnPress(RenderTarget& data, RenderTarget& tmp, 
                            MouseCondition mouse, Color color)
{
    start_pos = mouse.position;
    drawing   = true;
}

void FillTool::PaintOnMove(RenderTarget& data, RenderTarget& tmp, 
                           MouseCondition mouse, Color color)
{
}

void FillTool::Disable()
{
    start_pos = Vector(1, -1);
}