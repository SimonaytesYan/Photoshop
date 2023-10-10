#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <cmath>

#include "../Renderable.h"
#include "../../Vector/Vector.h"
#include "../../List.h"
#include "../../Keys.h"
#include "../../RegionSet/RegionSet.h"

enum Events
{
    KEY_PRESS,
    KEY_RELEASE,
    MOUSE_PRESS,
    MOUSE_RELEASE,
    MOUSE_MOVE
};

class Widget : public Renderable
{

protected:
    bool          available;
    List<Widget*> sub_widgets;
    Vector        position;
    RegionSet     reg_set;

public : 
    Widget (Vector position = Vector(0, 0), bool available = true);
    virtual ~Widget();

    virtual void Render        (RenderTarget* render_target) override;
    virtual void AddObject     (Widget* new_widget);

    virtual bool OnKeyPress    (Key key);
    virtual bool OnKeyRelease  (Key key);
    virtual bool OnMousePress  (MouseCondition mouse);
    virtual bool OnMouseRelease(MouseCondition mouse);
    virtual bool OnMouseMove   (MouseCondition mouse);

    Vector GetPosition();
};

#endif  //SYM_SUB_WINDOW