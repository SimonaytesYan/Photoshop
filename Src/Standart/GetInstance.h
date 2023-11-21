#ifndef SYM_GET_INSTANCE
#define SYM_GET_INSTANCE

#include "App.h"
#include "Plugin.h"

extern "C" plugin::Plugin* getInstance(plugin::App *app);

#endif //SYM_GET_INSTANCE