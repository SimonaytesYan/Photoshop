#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <cmath>

#include "../Renderable.h"
#include "../../Vector/Vector.h"
#include "../../List.h"
#include "../../Keys.h"
#include "../../RegionSet/RegionSet.h"
#include "../../Event.h"
#include "../../EventProcessable.h"

class Widget;
using transform_f =  Widget*(*)(Widget *, void *);
using check_f     =  bool   (*)(Widget *, void *);

class Widget : public Renderable, public EventProcessable
{

protected:
    bool          available;
    List<Widget*> sub_widgets;
    Vector        position;
    Vector        size;
    RegionSet     reg_set;
    RegionSet     default_reg_set;
    Widget*       parent;

public : 
    Widget (Vector position = Vector(0, 0), Vector size = Vector(0,0), bool available = true);
    virtual ~Widget();

    virtual bool OnKeyPress    (Key key)              override;
    virtual bool OnKeyRelease  (Key key)              override;
    virtual bool OnMousePress  (MouseCondition mouse) override;
    virtual bool OnMouseRelease(MouseCondition mouse) override;
    virtual bool OnMouseMove   (MouseCondition mouse) override;
    virtual bool OnClock       (size_t delta)         override;

    virtual void Render                (RenderTarget* render_target) override;
    virtual void Move                  (Vector delta);
    virtual void AddObject             (Widget* new_widget);
    void         ToForeground          (Widget* son);

    const RegionSet& GetDefaultRegSet() const { return default_reg_set; }
    RegionSet&       GetRegionSet()           { return reg_set; }
    const RegionSet& GetRegionSet()    const  { return reg_set; }
    void             UpdateRegionSet        (bool debug = false);
    void             UpdateRegionSetFromRoot(bool debug = false);
    void             UpdateDefaultRegionSet();
    void             UpdateParentDefaultRegionSet();
    virtual void     UpdateOwnDefaultRegionSet();
    void             RemoveSon              (Widget* son);
    
    virtual bool  InsideP(Vector v);

    Vector&       GetSize()            { return size;      }
    const Vector& GetSize()      const { return size;      }
    Vector        GetPosition()  const { return position;  }
    bool          GetAvailable() const { return available; }
    Widget*       GetParent()    const { return parent;    }

    void          SetAvailable(bool new_available) { available = new_available; }
};

class RectangleWidget : public Widget
{
    Color background;

public:
    RectangleWidget(Vector position = Vector(0, 0), Vector size = Vector(0,0),
                    Color background = Color(255, 255, 255), bool available = true) :
    Widget     (position, size, available),
    background (background)
    {}

    void Render(RenderTarget* render_target)
    {
        render_target->DrawRect(position, size, reg_set, background);
        Widget::Render(render_target);
    }
};

#endif  //SYM_SUB_WINDOW