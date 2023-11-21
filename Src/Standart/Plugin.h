#ifndef SYM_PLUGIN
#define SYM_PLUGIN

#include "Interface.h"

namespace plugin
{
    struct Plugin 
    {
        /* где-то тут лежит App*, но это дело автора плагина */
        uint64_t       id;
        const char    *name;
        InterfaceType  type;

        virtual Interface *getInterface() = 0;
        virtual ~Plugin() = 0;
    };

}

#endif //SYM_PLUGIN