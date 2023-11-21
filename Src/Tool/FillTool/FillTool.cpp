#include "FillTool.h"
#include "../../Texture/Texture.h"
#include "../../RenderTarget/RenderTarget.h"
#include "../../RegionSet/RegionSet.h"
#include "../../ClipRegion/ClipRegion.h"
#include "../../Useful.h"

const size_t  kTransNumb               = 4;
const plugin::VectorI kTransitions[kTransNumb] = {plugin::VectorI(1,  0), 
                                          plugin::VectorI(0,  1), 
                                          plugin::VectorI(-1, 0), 
                                          plugin::VectorI(0,  -1)};

bool GoToPixelP(plugin::VectorI cur, plugin::VectorI next, 
                plugin::VectorI size, const u_int8_t* pixels, bool** visited)
{
    return 0 <= next.x && next.x < size.x &&
           0 <= next.y && next.y < size.y &&
           *GetC(pixels, size, cur) == *GetC(pixels, size, next) &&
           !visited[next.y][next.x];
}

void AddTransitions(DynArray<plugin::VectorI> &stack, plugin::VectorI cur,
                    const u_int8_t* pixels, plugin::VectorI size, bool** visited)
{
    for (int i = 0; i < kTransNumb; i++)
    {
        plugin::VectorI next = cur + kTransitions[i];

        if (GoToPixelP(cur, next, size, pixels, visited))
            stack.PushBack(next);
    }
}

void FillTool::paintOnRelease(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                              MouseContext mouse, plugin::Color color)
{
    if (drawing)
    {
        DynArray<plugin::VectorI> stack(0);

        Image img(((RenderTarget*)data)->GetTexture());

        plugin::VectorI         size(0, 0);
        const u_int8_t* pixels  = img.GetPixelArray(size);

        if (*GetC(pixels, size, start_pos) == color)
        {
            drawing = false;
            return;
        }

        bool** visited = (bool**)calloc(sizeof(bool*), size.y);
        for (int i = 0; i < size.y; i++)
            visited[i] = (bool*)calloc(sizeof(bool), size.x);

        stack.PushBack(start_pos);

        while (stack.GetLength() != 0)
        {
            plugin::VectorI cur = stack[stack.GetLength() - 1];

            plugin::Color* clr = GetC(pixels, size, cur);
            visited[cur.y][cur.x] = true;

            stack.PopBack();
            
            //Add in stack neighboring pixels
            AddTransitions(stack, cur, pixels, size, visited);

            //Colorize cur pixel
            *GetC(pixels, size, cur) = color;
        }

        Texture res_texture;
        res_texture.LoadFromImage(img);
        ((RenderTarget*)data)->DrawSprite(plugin::Vec2(0, 0), res_texture);

        drawing = false;
    }
}


void FillTool::paintOnPress(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                            MouseContext mouse, plugin::Color color)
{
    start_pos = mouse.position;
    drawing   = true;
}

void FillTool::paintOnMove(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, 
                           MouseContext mouse, plugin::Color color)
{
}

void FillTool::disable(plugin::RenderTargetI* data,  plugin::RenderTargetI* tmp, 
                       MouseContext mouse, plugin::Color         color)
{
    if (drawing)
    {
        start_pos = plugin::Vec2(1, -1);
        drawing   = false;
    }
}
