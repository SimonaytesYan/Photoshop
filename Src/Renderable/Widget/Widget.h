#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <cmath>

#include "../../Event.h"
#include "../../Standart/Standart.h"
#include "../../List.h"
#include "../Renderable.h"
#include "../../RegionSet/RegionSet.h"
#include "../../EventProcessable.h"

class Widget : public Renderable, public plugin::WidgetI, public EventProcessable
{
protected:
    uint8_t priority;
    bool            available;
    List<Widget*>   sub_widgets;
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

    virtual bool onKeyboardPress    (plugin::KeyboardContext key) override;
    virtual bool onKeyboardRelease  (plugin::KeyboardContext key) override;
    virtual bool onMousePress       (plugin::MouseContext mouse)  override;
    virtual bool onMouseRelease     (plugin::MouseContext mouse)  override;
    virtual bool onMouseMove        (plugin::MouseContext mouse)  override;
    virtual bool onClock            (size_t delta)                override;

    virtual void render             (plugin::RenderTargetI* render_target) override;
    virtual void move               (plugin::Vec2 delta)                   override;
    virtual void registerSubWidget  (WidgetI* new_widget)                  override;
            void unregisterSubWidget(WidgetI* son)                         override;

    bool         getAvailable() const override { return available; }
    plugin::Vec2 getSize     () const override { return size;      }
    plugin::Vec2 getPos      () const override { return position;  }
    WidgetI*     getParent   () const override { return parent;    }
    uint8_t      getPriority () override { return priority;  }

    void setAvailable(bool value)             override { available = value;         }
    void setSize     (plugin::Vec2 value)     override { size      = value;         }
    void setPos      (plugin::Vec2 value)     override { position  = value;         }
    void setParent   (plugin::WidgetI* value) override { parent    = (Widget*)value;}
    
    virtual void render       (RenderTarget* render_target);
    void         ToForeground (Widget* son);

    const RegionSet& GetDefaultRegSet() const { return default_reg_set; }
    RegionSet&       GetRegionSet()           { return reg_set; }
    const RegionSet& GetRegionSet()    const  { return reg_set; }
    void             recalcRegion();
    void             UpdateRegionSet       ();
    void             UpdateDefaultRegionSet();
    void             UpdateParentDefaultRegionSet();
    virtual void     UpdateOwnDefaultRegionSet();
    
    virtual bool InsideP(plugin::Vec2 v);    
};

//============================PLUGIN WIDGET=====================================

class PluginWidget : public Widget
{
    plugin::PluginWidgetI* plugin_widget_i;

public :

    PluginWidget(plugin::PluginWidgetI* widget) :
    plugin_widget_i (widget)
    { }

    void render(plugin::RenderTargetI* render_target) override;

    bool onKeyboardPress    (plugin::KeyboardContext key) override;
    bool onKeyboardRelease  (plugin::KeyboardContext key) override;
    bool onMousePress       (plugin::MouseContext mouse)  override;
    bool onMouseRelease     (plugin::MouseContext mouse)  override;
    bool onMouseMove        (plugin::MouseContext mouse)  override;
    bool onClock            (size_t delta)                override;
};

#endif  //SYM_SUB_WINDOW