#ifndef SYM_APP
#define SYM_APP

#include "GuiI.h"
#include "EventManagerI.h"
#include "ToolI.h"
#include "FilterI.h"

namespace plugin
{
    struct App
    {
        GuiI *root;
        EventManagerI *event_manager; 
        ToolManagerI *tool_manager;
        FilterManagerI *filter_manager; 
    };
}
#endif //SYM_APP