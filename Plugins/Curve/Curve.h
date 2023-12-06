#ifndef SYM_CURVE_PLUGIN
#define SYM_CURVE_PLUGIN

#include "../../Src/Standart/Standart.h"
#include "../../Src/List.h"

namespace sym_plugin
{

    const int           kCurvePointSize = 15;
    const plugin::Color kCurveColorR(255,   0,   0);
    const plugin::Color kCurveColorG(  0, 255,   0);
    const plugin::Color kCurveColorB(  0,   0, 255);

    class CurveFilter;
    
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

    enum Events
    {
        MOUSE_PRESS,
        MOUSE_RELEASE,
        MOUSE_MOVE,
        KEY_PRESS,
        KEY_RELEASE,
        ON_CLOCK,
        EVENTS_NUMBER
    };

    class Widget : public plugin::WidgetI
    {
    protected:
        uint8_t          priority;
        bool             available;
        plugin::Vec2     position;
        plugin::Vec2     size;
        List<plugin::WidgetI*>  sub_widgets;
        plugin::WidgetI* parent;

    public: 
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
        bool         isExtern    () override { return true;     }
        uint8_t      getPriority () override { return priority;  }
        WidgetI*     getParent   () override { return parent;    }

        void setAvailable(bool value)             override { available = value;         }
        void setSize     (plugin::Vec2 value)     override { size      = value;         }
        void setPos      (plugin::Vec2 value)     override { position  = value;         }
        void setParent   (plugin::WidgetI* value) override { parent    = (Widget*)value;}    
        
        void setPriority(uint8_t value) { priority = value;  }
        void setParent  (Widget* value) { parent   = value;  };

        virtual bool InsideP(plugin::Vec2 v);
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
               ButtonFunction* _on_release = nullptr) :
        Widget           (_position, _size),
        on_press         (_on_press),
        on_release       (_on_release),
        background_color (_background_color),
        pressed          (false)
        {}

        ~Button()
        {}

        void ChangePressFunction(ButtonFunction* new_on_press)
        {
            on_press = new_on_press;
        }

        void SetColor(plugin::Color color) { background_color = color; }

        virtual void render        (plugin::RenderTargetI* render_target) override;
                bool onMousePress  (plugin::MouseContext   mouse)         override;
                bool onMouseRelease(plugin::MouseContext   mouse)         override;
                bool onMouseMove   (plugin::MouseContext   mouse)         override;
    };

    class CurveWindow;

    struct ApplyFilterFunctor : public ButtonFunction
    {
        CurveWindow* window;
        CurveFilter* filter;
        plugin::RenderTargetI* rt;
        plugin::Array<uint8_t> r;
        plugin::Array<uint8_t> g;
        plugin::Array<uint8_t> b;

        ApplyFilterFunctor() :
        filter (nullptr),
        rt     (nullptr),
        window (nullptr),
        r      (plugin::Array<uint8_t>()),
        g      (plugin::Array<uint8_t>()),
        b      (plugin::Array<uint8_t>())
        {}

        void operator()() override
        {
            delete window;
            filter->apply(rt, r, g, b);
        }
    };

    //=============================CURVE WINDOW=================================

    const plugin::Color kSelected  (128, 128, 128);
    const plugin::Color kUnSelected(50,  50,  50);

    enum class CurveWindowStatus
    {
        Red,
        Green,
        Blue
    };

    class CurveWindow : public Widget
    {
        plugin::App*        app;
        ApplyFilterFunctor* functor;

        List<plugin::Vec2>  points_r;
        List<plugin::Vec2>  points_g;
        List<plugin::Vec2>  points_b;

        CurveWindowStatus status;

        int moving_point_index;

        void ProcessPoint(List<plugin::Vec2>& points, plugin::Vec2 position);
        void MovePoint(plugin::Vec2 mouse_pos);
        void AddPoint (List<plugin::Vec2> &points, plugin::Vec2 pos);
        void DrawCurve(plugin::RenderTargetI* target,
                       List<plugin::Vec2> &points, 
                       plugin::Color color);

    public :

        Button* red_button;
        Button* green_button;
        Button* blue_button;

        CurveWindow(plugin::Vec2 pos, plugin::Vec2 size, ApplyFilterFunctor* functor, plugin::App* app);
        
        ~CurveWindow();
        
        void SetStatus(CurveWindowStatus new_status) 
        { 
            status = new_status;

            red_button  ->SetColor(kUnSelected);
            green_button->SetColor(kUnSelected);
            blue_button ->SetColor(kUnSelected);
            
            switch (new_status)
            {
                case CurveWindowStatus::Red:
                    red_button->SetColor(kSelected);
                    break;
                case CurveWindowStatus::Green:
                    green_button->SetColor(kSelected);
                    break;
                case CurveWindowStatus::Blue:
                    blue_button->SetColor(kSelected);
                    break;
                default:
                    break;
            }
        } 

        void render        (plugin::RenderTargetI* target) override;
        bool onMousePress  (plugin::MouseContext mouse)    override;
        bool onMouseMove   (plugin::MouseContext mouse)    override;
        bool onMouseRelease(plugin::MouseContext mouse)    override;
    };


    struct ChangeStatusFunctor : ButtonFunction
    {
        CurveWindowStatus status_to_set;
        CurveWindow*      window;

        ChangeStatusFunctor(CurveWindowStatus status, 
                                       CurveWindow*      window) :
        status_to_set (status),
        window        (window)
        { }

        void operator()() override
        {
            fprintf(stderr, "Change status to %d\n", status_to_set);
            window->SetStatus(status_to_set);
        }
    };

    //===============================LABEL======================================

    class Label : public Widget
    {
        int   character_size;
        char* text;
        plugin::Color text_color;
        plugin::Color background;

    public:
        Label(plugin::Vec2 _position, int character_size, 
            const char* text = "Label", plugin::Color background = plugin::Color(0, 0, 0), 
            plugin::Color text_color = plugin::Color(255, 255, 255));
        ~Label();

        void SetText(const char* new_text);

        void render(plugin::RenderTargetI* render_target) override;
    };
};

#endif //SYM_CURVE_PLUGIN