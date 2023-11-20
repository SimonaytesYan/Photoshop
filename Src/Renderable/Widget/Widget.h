#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <cmath>

#include "../../Event.h"
#include "../../EventProcessable.h"
#include "../../Keys.h"
#include "../../List.h"
#include "../Renderable.h"
#include "../../RegionSet/RegionSet.h"
#include "../../Standart/WidgetI.h"
#include "../../Vec2/Vec2.h"

class Widget;

struct WidgetPtr
{
    union 
    {
        Widget*          widget;
        plugin::WidgetI* widget_i;
    };
    bool is_extern;

    WidgetPtr(plugin::WidgetI* object)
    {
        if (widget->isExtern())
        {
            is_extern = true;
            widget_i  = object;
        }
        else
        {
            is_extern = true;
            widget    = (Widget*)object;
        }
    }

    RegionSet GetDefaultRegSet()
    {
        if (is_extern)
        {
            RegionSet reg_set;
            reg_set.AddRegion(ClipRegion(widget_i->getPos(), widget_i->getSize()));
            return reg_set;   
        }
        
        return GetDefaultRegSet();
    }
};

class Widget : public Renderable, public plugin::WidgetI, public EventProcessable
{

protected:
    bool            available;
    List<WidgetPtr> sub_widgets;
    plugin::Vec2    position;
    plugin::Vec2    size;
    RegionSet       reg_set;
    RegionSet       default_reg_set;
    Widget*         parent;

public : 
    Widget (plugin::Vec2 position = plugin::Vec2(0, 0), plugin::Vec2 size = plugin::Vec2(0,0), bool available = true);
    virtual ~Widget();

    virtual bool onKeyboardPress    (KeyboardContext key) override;
    virtual bool onKeyboardRelease  (KeyboardContext key) override;
    virtual bool onMousePress  (MouseContext mouse)  override;
    virtual bool onMouseRelease(MouseContext mouse)  override;
    virtual bool onMouseMove   (MouseContext mouse)  override;
    virtual bool onClock       (size_t delta)        override;

    virtual void Render                (RenderTarget* render_target) override;
    virtual void Move                  (plugin::Vec2 delta);
    virtual void registerSubWidget     (WidgetI* new_widget);
    void         ToForeground          (Widget* son);

    const RegionSet& GetDefaultRegSet() const { return default_reg_set; }
    RegionSet&       GetRegionSet()           { return reg_set; }
    const RegionSet& GetRegionSet()    const  { return reg_set; }
    void             UpdateRegionSet        (bool debug = false);
    void             recalcRegion(bool debug = false);
    void             UpdateDefaultRegionSet();
    void             UpdateParentDefaultRegionSet();
    virtual void     UpdateOwnDefaultRegionSet();
    void             RemoveSon              (Widget* son);
    
    virtual bool InsideP(plugin::Vec2 v);

    plugin::Vec2&       GetSize()            { return size;      }
    const plugin::Vec2& GetSize()      const { return size;      }
    plugin::Vec2        GetPosition()  const { return position;  }
    bool          GetAvailable() const { return available; }
    Widget*       GetParent()    const { return parent;    }

    void          SetAvailable(bool new_available) { available = new_available; }
};

class RectangleWidget : public Widget
{
    plugin::Color background;

public:
    RectangleWidget(plugin::Vec2 position = plugin::Vec2(0, 0), plugin::Vec2 size = plugin::Vec2(0,0),
                    plugin::Color background = plugin::Color(255, 255, 255), bool available = true) :
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