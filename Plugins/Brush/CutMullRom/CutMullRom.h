#ifndef SYM_CUT_MULL_ROM
#define SYM_CUT_MULL_ROM

#include "../../../Src/RenderTarget/RenderTarget.h"
#include "../../../Src/List.h"

namespace sym_cut_mul_rom_brush
{
    void DrawUsingCatMullRom_plugin(plugin::RenderTargetI* data, 
                                    plugin::RenderTargetI* tmp, plugin::Color color,
                                    double thickness, List<plugin::Vec2> &vertexes);
    void DrawTmpToData_plugin(plugin::RenderTargetI* data, 
                              plugin::RenderTargetI* tmp, plugin::Color color, 
                              double thickness, List<plugin::Vec2> &vertexes);
}

#endif