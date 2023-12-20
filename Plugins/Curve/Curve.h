#ifndef SYM_CURVE_PLUGIN
#define SYM_CURVE_PLUGIN

#include "../../Src/Standart/Standart.h"
#include "../../Src/List.h"
#include "../../Src/Useful.h"
#include "CutMullRom.h"

namespace sym_plugin
{
    const plugin::Color kSelected  (220, 220, 220);
    const plugin::Color kUnSelected(180, 180, 180);

    const int           kThickness      = 3;
    const int           kCurvePointSize = 10;
    const plugin::Color kCurveColorR(255,   0,   0);
    const plugin::Color kCurveColorG(  0, 255,   0);
    const plugin::Color kCurveColorB(  0,   0, 255);

    const plugin::Color kBackgroundColor(255, 255, 255);
    const plugin::Color kTextColor      ( 61,  61,  61);
    const plugin::Vec2  kButtonSize     (75, 30);
    const int           kTextSize     = 20;

    class CurveFilter;
    
    class CurvePlugin : public plugin::Plugin
    {
        CurveFilter* filter;
        plugin::App* app;
    
    public:

        CurvePlugin(plugin::App* app);

        plugin::Interface *getInterface() const override
        { return (plugin::Interface*) filter; }

        void selectPlugin() override
        {}

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
        parent (parent),
        param_names (plugin::Array<const char*>(0, nullptr))
        {}

        void                       apply        (plugin::RenderTargetI* rt)    override;
        void                       setParams    (plugin::Array<double> params) override;
        plugin::Array<const char*> getParamNames()                       const override;
        plugin::Array<double>      getParams    ()                       const override;

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

    class Widget : public plugin::PluginWidgetI
    {
    protected:
        uint8_t                       priority;
        plugin::Vec2                  position;
        plugin::Vec2                  size;

    public: 
        Widget (plugin::Vec2 position = plugin::Vec2(0, 0), 
                plugin::Vec2 size     = plugin::Vec2(0, 0));
        virtual ~Widget();

        virtual bool onKeyboardPress    (plugin::KeyboardContext key) override;
        virtual bool onKeyboardRelease  (plugin::KeyboardContext key) override;
        virtual bool onMousePress       (plugin::MouseContext mouse)  override;
        virtual bool onMouseRelease     (plugin::MouseContext mouse)  override;
        virtual bool onMouseMove        (plugin::MouseContext mouse)  override;
        virtual bool onClock            (size_t delta)                override;

        virtual void move(plugin::Vec2 shift);

        virtual void render(plugin::RenderTargetI* render_target) override;

        uint8_t      getPriority () const override { return priority;  }

        void setPriority(uint8_t value) { priority = value; }

        plugin::Vec2 getPos()  const { return position; }
        plugin::Vec2 getSize() const { return size; }

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
        r      (plugin::Array<uint8_t>(0, nullptr)),
        g      (plugin::Array<uint8_t>(0, nullptr)),
        b      (plugin::Array<uint8_t>(0, nullptr))
        {}

        void operator()() override;
    };

    //=============================CURVE WINDOW=================================

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

        plugin::Vec2 graph_size;
        plugin::Vec2 graph_pos;

        bool         moving;
        plugin::Vec2 last_mouse_pos;

        void UpdateFilter(plugin::Texture* texture);
        void ProcessPoint(List<plugin::Vec2>& points, plugin::Vec2 position);
        void MovePoint   (plugin::Vec2 mouse_pos);
        void AddPoint    (List<plugin::Vec2> &points, plugin::Vec2 pos);
        void DrawCurve   (plugin::RenderTargetI* target,
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

        void Close()
        { 
            host->setAvailable(false);
        }

        void SetMoving(bool value)
        { moving = value; }

        void render        (plugin::RenderTargetI* target) override;
        bool onMousePress  (plugin::MouseContext mouse)    override;
        bool onMouseMove   (plugin::MouseContext mouse)    override;
        bool onMouseRelease(plugin::MouseContext mouse)    override;
        void move          (plugin::Vec2 delta)            override;
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
            window->SetStatus(status_to_set);
        }
    };

    //===============================LABEL======================================

    class Label : public Widget
    {
        int   character_size;
        char* text;
        plugin::Color text_color;

    public:
        Label(plugin::Vec2 _position, int character_size, 
            const char* text = "Label",
            plugin::Color text_color = plugin::Color(255, 255, 255));
        ~Label();

        void SetText(const char* new_text);

        void render(plugin::RenderTargetI* render_target) override;
    };
};

#endif //SYM_CURVE_PLUGIN