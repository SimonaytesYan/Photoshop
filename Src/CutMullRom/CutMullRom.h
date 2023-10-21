#ifndef SYM_CUT_MULL_ROM
#define SYM_CUT_MULL_ROM

#include "../RenderTarget/RenderTarget.h"
#include "../List.h"

void DrawUsingCatMullRom(RenderTarget& data, RenderTarget& tmp, Color color,
                         double thickness, List<Vector> &vertexes);
void DrawTmpToData      (RenderTarget& data, RenderTarget& tmp, Color color, 
                        double thickness, List<Vector> &vertexes);

#endif