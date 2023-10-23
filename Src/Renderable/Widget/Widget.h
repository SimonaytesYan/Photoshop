#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <cmath>

#include "../Renderable.h"
#include "../../Vector/Vector.h"
#include "../../List.h"
#include "../../Keys.h"
#include "../../RegionSet/RegionSet.h"
#include "../../EventProcessable.h"

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

class Widget : public Renderable, public EventProcessable
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

    virtual bool OnKeyPress    (Key key)              override;
    virtual bool OnKeyRelease  (Key key)              override;
    virtual bool OnMousePress  (MouseCondition mouse) override;
    virtual bool OnMouseRelease(MouseCondition mouse) override;
    virtual bool OnMouseMove   (MouseCondition mouse) override;
    virtual bool OnClock       (u_int64_t delta)      override
    {};

    virtual void Render        (RenderTarget* render_target) override;
    virtual void Move          (Vector delta);
    virtual void AddObject     (Widget* new_widget);
    
    RegionSet&       GetRegionSet()       { return reg_set; }
    const RegionSet& GetRegionSet() const { return reg_set; }
    void             UpdateRegionSet();
    void             UpdateRegionSetFromRoot();

    Vector&       GetSize()       { return size; }
    const Vector& GetSize() const { return size; }
    Vector        GetPosition();
    bool          InsideP(Vector v);
};

#endif  //SYM_SUB_WINDOW