#ifndef SYM_TOOL_I
#define SYM_TOOL_I

#include "Interface.h"
#include "RenderTargetI.h"
#include "../Color.h"
#include "../Keys.h"

namespace plugin
{
    struct ToolI: public Interface 
    {
        virtual const Texture *getIcon() = 0;

        virtual void paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, 
                                    MouseContext context, Color color) = 0;
        virtual void paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, 
                                    MouseContext context, Color color) = 0;
        virtual void paintOnMove   (RenderTargetI *data, RenderTargetI *tmp, 
                                    MouseContext context, Color color) = 0;
        virtual void disable       (RenderTargetI *data, RenderTargetI *tmp, 
                                    MouseContext context, Color color) = 0;
    };

    struct ToolManagerI 
    {
        virtual void setColor(Color color) = 0;
        virtual void setTool (ToolI *tool)         = 0;

        virtual ToolI* getTool () = 0;
        virtual Color  getColor() = 0;

        virtual void paintOnMove   (RenderTargetI *data, RenderTargetI *tmp, 
                                    MouseContext context) = 0;
        virtual void paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, 
                                    MouseContext context) = 0;
        virtual void paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, 
                                    MouseContext context) = 0;
        virtual void disableTool   (RenderTargetI *data, RenderTargetI *tmp, 
                                    MouseContext context) = 0;
    };
}

#endif //SYM_TOOL_I