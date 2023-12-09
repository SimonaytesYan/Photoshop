#ifndef SYM_CUT_MULL_ROM
#define SYM_CUT_MULL_ROM

#include "../../Src/RenderTarget/RenderTarget.h"
#include "../../Src/List.h"

namespace sym_plugin
{
    bool DrawUsingCatMullRom_plugin(plugin::RenderTargetI* target, plugin::Color color,
                                    double thickness, List<plugin::Vec2> &vertexes, 
                                    plugin::Vec2 graph_pos, plugin::Vec2 graph_size);
}

#endif