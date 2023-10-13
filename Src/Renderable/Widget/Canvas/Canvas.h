#ifndef SYM_CANVAS
#define SYM_CANVAS

#include "../Widget.h"
//#include "../../../ToolManager/ToolManager.h" 

class Canvas : public Widget
{
    ToolManager* tm;
    RenderTarget data;

public :
    Canvas();

    Canvas(const Canvas& b);
    ~Canvas();
    Canvas& operator=(const Canvas& b); 
};

#endif //SYM_CANVAS