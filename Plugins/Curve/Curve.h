#ifndef SYM_CURVE_PLUGIN
#define SYM_CURVE_PLUGIN

#include "../../Src/Standart/Standart.h"
#include "../../Src/List.h"
#include "../../Src/Font/Font.h"

class CurveFilter;

namespace sym_plugin
{
    class CurvePlugin : public plugin::Plugin
    {
        CurveFilter* filter;
        plugin::App* app;
    
    public:

        CurvePlugin(plugin::App* app);

        plugin::Interface *getInterface() override
        { return (plugin::Interface*) filter; }

        ~CurvePlugin()
        {}

        void CreateCurveWindow(plugin::RenderTargetI* rt);
    };

    class CurveFilter : public plugin::FilterI
    {
        CurvePlugin*               parent;
        plugin::Array<const char*> param_names;

    public:
        CurveFilter(CurvePlugin* parent) :
        parent (parent)
        {}

        void                       apply        (plugin::RenderTargetI* rt)    override;
        void                       setParams    (plugin::Array<double> params) override;
        plugin::Array<const char*> getParamNames()                             override;
        plugin::Array<double>      getParams    ()                             override;

        void apply(plugin::RenderTargetI* rt,
                   plugin::Array<uint8_t> r, 
                   plugin::Array<uint8_t> g, 
                   plugin::Array<uint8_t> b);

        ~CurveFilter()
        {}
    };

    //======================================WIDGET==============================

    class Widget;

    enum Events
    {
        KEY_RELEASE,
        KEY_PRESS,
        MOUSE_MOVE,
        MOUSE_PRESS,
        MOUSE_RELEASE,
        ON_CLOCK,
        EVENTS_NUMBER
    };

    struct WidgetPtr
    {
        union 
        {
            Widget*          widget;
            plugin::WidgetI* widget_i;
        };
        bool is_extern;

        WidgetPtr(plugin::WidgetI* object);

        plugin::Vec2 getSize();
        plugin::Vec2 getPos();
        bool         onKeyboardPress  (plugin::KeyboardContext key);
        bool         onKeyboardRelease(plugin::KeyboardContext key);
        bool         onMousePress     (plugin::MouseContext mouse);
        bool         onMouseRelease   (plugin::MouseContext mouse);
        bool         onMouseMove      (plugin::MouseContext mouse);
        bool         onClock          (size_t delta);
        void         move             (plugin::Vec2 shift);
        bool         InsideP          (plugin::Vec2 v);
        void         setAvailable     (bool value);
        bool         getAvailable     ();
    };

    class Widget : public plugin::WidgetI
    {
    protected:
        uint8_t          priority;
        bool             available;
        plugin::Vec2     position;
        plugin::Vec2     size;
        List<WidgetPtr>  sub_widgets;
        plugin::WidgetI* parent;

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
        
        void setPriority(uint8_t value) { priority = value;  }

        virtual bool InsideP(plugin::Vec2 v);
    };


    class CurveWindow : public Widget
    {
    public :
        CurveWindow(plugin::Vec2 pos, plugin::Vec2 size) :
        Widget(pos, size)
        {}

        plugin::RenderTargetI* rt;

        void render(plugin::RenderTargetI* target) override;
    };

    //===============================BUTTON=====================================
    
    struct ButtonFunction
    {
        virtual void operator()() = 0;
        virtual ~ButtonFunction()
        {}
    };

    class Button : public Widget
    {
    protected :
        ButtonFunction* on_press;
        ButtonFunction* on_release;
        bool            pressed;
        plugin::Color   background_color;       //use only if texture_button == false

    public :
        Button(plugin::Vec2   _position, 
               plugin::Vec2   _size, 
               plugin::Color    _background_color,
               ButtonFunction* _on_press   = nullptr,
               ButtonFunction* _on_release = nullptr);
        ~Button();

        void ChangePressFunction(ButtonFunction* new_on_press)
        {
            on_press = new_on_press;
        }

        virtual void render        (plugin::RenderTargetI* render_target) override;
                bool onMousePress  (plugin::MouseContext   mouse)         override;
                bool onMouseRelease(plugin::MouseContext   mouse)         override;
                bool onMouseMove   (plugin::MouseContext   mouse)         override;
    };

    class TextButton : public Button
    {
        public :
        TextButton(plugin::Vec2   _position, plugin::Vec2   _size, 
                   plugin::Color    _background_color,
                   Font font, int character_size, const char* text = "Button",
                   plugin::Color text_color = plugin::Color(0, 0, 0),
                   ButtonFunction*  _on_press   = nullptr,
                   ButtonFunction*  _on_release = nullptr);
    };

    struct ApplyFilterFunctor : public ButtonFunction
    {
        CurveFilter* filter;
        plugin::RenderTargetI* rt;
        plugin::Array<uint8_t> r;
        plugin::Array<uint8_t> g;
        plugin::Array<uint8_t> b;

        void operator()() override
        {
            filter->apply(rt, r, g, b);
        }
    };
}

#endif //SYM_CURVE_PLUGIN