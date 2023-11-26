#ifndef SYM_APP
#define SYM_APP

#include "Standart.h"
#include "Standart.h"
#include "Standart.h"
#include "Standart.h"

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