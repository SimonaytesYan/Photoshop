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

    WidgetPtr(plugin::WidgetI* object);

    RegionSet    GetDefaultRegSet ();
    plugin::Vec2 getSize();
    plugin::Vec2 getPos();
    bool         onKeyboardPress  (KeyboardContext key);
    bool         onKeyboardRelease(KeyboardContext key);
    bool         onMousePress     (MouseContext mouse);
    bool         onMouseRelease   (MouseContext mouse);
    bool         onMouseMove      (MouseContext mouse);
    bool         onClock          (size_t delta);
    void         move             (plugin::Vec2 shift);
    bool         InsideP          (plugin::Vec2 v);
    void         setAvailable     (bool value);
    bool         getAvailable     ();
    void         recalcRegion     ();
};

class Widget : public Renderable, public plugin::WidgetI
{
protected:
    uint8_t priority;
    bool            available;
    List<WidgetPtr> sub_widgets;
    plugin::Vec2    position;
    plugin::Vec2    size;
    RegionSet       reg_set;
    RegionSet       default_reg_set;
    Widget*         parent;

public : 
    Widget (plugin::Vec2 position = plugin::Vec2(0, 0), 
            plugin::Vec2 size     = plugin::Vec2(0, 0), 
            bool available = true);
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
            void recalcRegion       ()                                     override;

    bool         getAvailable() override { return available; }
    plugin::Vec2 getSize     () override { return size;      }
    plugin::Vec2 getPos      () override { return position;  }
    bool         isExtern    () override { return false;     }
    uint8_t      getPriority () override { return priority;  }
    WidgetI*     getParent   () override { return parent;    }

    void setAvailable(bool value)             override { available = value;         }
    void setSize     (plugin::Vec2 value)     override { size      = value;         }
    void setPos      (plugin::Vec2 value)     override { position  = value;         }
    void setParent   (plugin::WidgetI* value) override { parent    = (Widget*)value;}
    
    virtual void render       (RenderTarget* render_target);
    void         ToForeground (Widget* son);

    const RegionSet& GetDefaultRegSet() const { return default_reg_set; }
    RegionSet&       GetRegionSet()           { return reg_set; }
    const RegionSet& GetRegionSet()    const  { return reg_set; }
    void             UpdateRegionSet       ();
    void             UpdateDefaultRegionSet();
    void             UpdateParentDefaultRegionSet();
    virtual void     UpdateOwnDefaultRegionSet();
    
    virtual bool InsideP(plugin::Vec2 v);

    const plugin::Vec2& getSize()      const { return size;      }
    plugin::Vec2        getPosition()  const { return position;  }
    
    bool          getAvailable() const { return available; }
    Widget*       getParent()    const { return parent;    }
};

#endif  //SYM_SUB_WINDOW