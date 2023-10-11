#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <cmath>

#include "../Renderable.h"
#include "../../Vector/Vector.h"
#include "../../List.h"
#include "../../Keys.h"
#include "../../RegionSet/RegionSet.h"

class Widget;
using transform_f =  Widget*(*)(Widget *, void *);
using check_f     =  bool   (*)(Widget *, void *);

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
    Vector        size;
    RegionSet     reg_set;
    Widget *      parent;

public : 
    Widget (Vector position = Vector(0, 0), Vector size = Vector(0,0), bool available = true);
    virtual ~Widget();

    virtual void Render        (RenderTarget* render_target) override;
    virtual void Move          (Vector delta);
    virtual void AddObject     (Widget* new_widget);

    virtual bool OnKeyPress    (Key key);
    virtual bool OnKeyRelease  (Key key);
    virtual bool OnMousePress  (MouseCondition mouse);
    virtual bool OnMouseRelease(MouseCondition mouse);
    virtual bool OnMouseMove   (MouseCondition mouse);

    Vector GetPosition();

    RegionSet&       GetRegionSet()       { return reg_set; }
    const RegionSet& GetRegionSet() const { return reg_set; }

    Vector&       GetSize()       { return size; }
    const Vector& GetSize() const { return size; }

    friend void RecursiveUpdate(Widget **widget_ptr, transform_f func, void* args, check_f check);
};



struct MinusRegionSetArgs {
    Widget *self;
    RegionSet *reg_set;
};

void RecursiveUpdate(Widget **widget, transform_f func, void* args, check_f check = nullptr);
Widget* ReturnRegionSet(Widget *widget, void *args_);
Widget* MinusRegionSet(Widget *widget, void *args_);
bool CheckSelfMinusRegion(Widget *const widget, void *args_);


#endif  //SYM_SUB_WINDOW