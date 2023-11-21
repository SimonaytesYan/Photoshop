#ifndef SYM_CUT_MULL_ROM
#define SYM_CUT_MULL_ROM

#include "../RenderTarget/RenderTarget.h"
#include "../List.h"

void DrawUsingCatMullRom(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::Color color,
                         double thickness, List<plugin::Vec2> &vertexes);
void DrawTmpToData      (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::Color color, 
                        double thickness, List<plugin::Vec2> &vertexes);

#endif