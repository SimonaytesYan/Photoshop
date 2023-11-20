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

    bool onKeyboardPress(KeyboardContext key)
    {
        if (is_extern)
            return widget_i->onKeyboardPress(key);
        return widget->onKeyboardPress(key);
    }

    bool onKeyboardRelease(KeyboardContext key)
    {
        if (is_extern)
            return widget_i->onKeyboardRelease(key);
        return widget->onKeyboardRelease(key);
    }

    bool onMousePress(MouseContext mouse) 
    {
        if (is_extern)
            return widget_i->onMousePress(mouse);
        return widget->onMousePress(mouse);
    }

    bool onMouseRelease(MouseContext mouse) 
    {
        if (is_extern)
            return widget_i->onMouseRelease(mouse);
        return widget->onMouseRelease(mouse);
    }

    bool onMouseMove(MouseContext mouse) 
    {
        if (is_extern)
            return widget_i->onMouseMove(mouse);
        return widget->onMouseMove(mouse);
    }

    bool onClock(size_t delta)       
    {
        if (is_extern)
            return widget_i->onClock(delta);
        return widget->onClock(delta);
    }

    bool getAvailable()
    {
        if (is_extern)
            return widget_i->getAvailable();
        return widget->getAvailable();
    }

    void recalcRegion()
    {
        if (is_extern)
            return widget_i->recalcRegion();
        return widget->recalcRegion();        
    }

    void move(plugin::Vec2 shift)
    {
        if (is_extern)
            return widget_i->move(shift);
        return widget->move(shift);
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
    virtual bool onMousePress       (MouseContext mouse)  override;
    virtual bool onMouseRelease     (MouseContext mouse)  override;
    virtual bool onMouseMove        (MouseContext mouse)  override;
    virtual bool onClock            (size_t delta)        override;

    virtual void render             (plugin::RenderTargetI* render_target) override;
    virtual void move               (plugin::Vec2 delta)                   override;
    virtual void registerSubWidget  (WidgetI* new_widget)                  override;
            void unregisterSubWidget(WidgetI* son)                         override;

    virtual void render             (RenderTarget* render_target);
    void         ToForeground      (Widget* son);

    const RegionSet& GetDefaultRegSet() const { return default_reg_set; }
    RegionSet&       GetRegionSet()           { return reg_set; }
    const RegionSet& GetRegionSet()    const  { return reg_set; }
    void             UpdateRegionSet        (bool debug = false);
    void             recalcRegion(bool debug = false);
    void             UpdateDefaultRegionSet();
    void             UpdateParentDefaultRegionSet();
    virtual void     UpdateOwnDefaultRegionSet();
    
    virtual bool InsideP(plugin::Vec2 v);

    plugin::Vec2&       GetSize()            { return size;      }
    const plugin::Vec2& GetSize()      const { return size;      }
    plugin::Vec2        GetPosition()  const { return position;  }
    bool          getAvailable() const { return available; }
    Widget*       GetParent()    const { return parent;    }

    void          setAvailable(bool new_available) { available = new_available; }
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

    void render(RenderTarget* render_target)
    {
        render_target->DrawRect(position, size, reg_set, background);
        Widget::render(render_target);
    }
};

#endif  //SYM_SUB_WINDOW