#ifndef SYM_STANDART
#define SYM_STANDART

#include <cinttypes>
#include <math.h>
#include <stdio.h>
#include <string.h>

namespace plugin {
    enum class InterfaceType {
        Tool,
        Filter,
        System // системный плагин, мб обертка
    };

/// @warning Array не владеющая структура => он не должен аллоцировать память. Даже в случае getPramas() надо возвращать указатель на какой-то внутренний массив даблов, а не аллоцировать, так как будет memory leak
    template<class T>
    struct Array 
    {
        uint64_t size;
        T* data;

        Array(uint64_t _size, T* _data) : 
        size(_size), 
        data(new T[_size]) {
            if (_data != nullptr)
                std::copy(_data, _data + _size, data);
        }

        Array(const Array<T>& other): 
        Array(other.size, other.data) 
        {}
        
        Array& operator=(const Array<T>& other) 
        {
            size = other.size;
            delete data;
            data = new T[other.size];
            std::copy(other.data, other.data + other.size, data);

	        return *this;
        }

        Array(Array<T>&& other) 
        {
            std::swap(size, other.size);
            std::swap(data, other.data);
        }

        Array& operator=(Array<T>&& other) 
        {
            std::swap(size, other.size);
            std::swap(data, other.data);

	        return *this;
        }

        ~Array() 
        {
            delete[] data;
        }
    };

    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Color() :
        r (0),
        g (0),
        b (0),
        a (255)
        {};
        
        Color(unsigned char _r, 
            unsigned char _g, 
            unsigned char _b, 
            unsigned char _a = 255) :
        r (_r),
        g (_g),
        b (_b),
        a (_a)
        {};

        Color Inverse()
        {
            return Color(255 - r, 255 - g, 255 - b);    
        }
    };

    static bool operator==(Color& a, Color& b)
    {
        return (a.a == b.a) && (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
    }

    struct Texture 
    {
        uint64_t height;
        uint64_t width;

        Color *pixels;

        Texture()
        {
            width  = 0;
            height = 0;
            pixels = nullptr;
        }

        Texture(const Texture& texture)
        {
            height = texture.height;
            width  = texture.width;

            pixels = new Color[height * width];
            memcpy(pixels, texture.pixels, sizeof(Color) * height * width);
        }

        virtual ~Texture()
        {
		    delete[] pixels;
	    }

        Texture& operator=(const Texture& other) 
        {
            height = other.height;
            width  = other.width;

            delete pixels;
            pixels = new Color[height * width];
            std::copy(other.pixels, other.pixels + height * width, pixels);

	        return *this;
        }

        Texture& operator=(Texture&& other) = default;
    };

    //================================VEC 2=====================================
    struct Vec2
    {
        double x;
        double y;

        Vec2()
        {
            x = y = 0;
        }
        Vec2(double _x, double _y)
        {
            x = _x;
            y = _y;
        }

        double GetX() const {return x;};
        double GetY() const {return y;};

        void   Dump  ()
        { fprintf(stderr, "(%.2lf, %.2lf)", x, y); }
        
        void   Rotate(double deg)
        {
            double rad = M_PI / 180 * deg;

            double rot_x = cos(rad);
            double rot_y = sin(rad);

            double old_x = x;
            double old_y = y;
            x = old_x * rot_x - old_y * rot_y;
            y = old_y * rot_x + old_x * rot_y;
        }

        double Length() const
        { return sqrt(x*x + y*y); }
        Vec2 operator+(const Vec2& b)
        { return Vec2(x + b.x, y + b.y); }
        Vec2 operator-(const Vec2& b)
        { return *this + Vec2(-b.x, -b.y); }
        Vec2 operator*(double b)
        { return Vec2(x * b, y * b); }
        Vec2 operator/(double b)
        { return Vec2(x / b, y / b); }

        bool operator==(const Vec2& b)
        { return x == b.x && y == b.y; }
    };

    static Vec2 operator*(double a, Vec2 b)
    {
        return Vec2(a * b.x, a * b.y);
    }

    static Vec2 operator-(Vec2 a)
    {
        return Vec2(-a.x, -a.y);
    }
    //==========================================================================

    enum class MouseButton {
        Left,
        Right,
        Unknown
    };

    /// @note см про относительность координат
    struct MouseContext 
    {
        Vec2        position;
        MouseButton button;
        MouseContext(Vec2 pos, MouseButton key)
        {
            position = pos;
            button   = key;
        }
    };

    enum class Key {
        Unknown = -1, 
        A = 0,        
        B,            
        C,            
        D,            
        E,            
        F,            
        G,            
        H,            
        I,            
        J,            
        K,            
        L,            
        M,            
        N,            
        O,            
        P,            
        Q,            
        R,            
        S,            
        T,            
        U,            
        V,            
        W,            
        X,            
        Y,            
        Z,            
        Num0,         
        Num1,         
        Num2,         
        Num3,         
        Num4,         
        Num5,         
        Num6,         
        Num7,         
        Num8,         
        Num9,         
        Escape,       
        LControl,     
        LShift,       
        LAlt,         
        LSystem,      
        RControl,     
        RShift,       
        RAlt,         
        RSystem,      
        Menu,         
        LBracket,     
        RBracket,     
        Semicolon,    
        Comma,        
        Period,       
        Apostrophe,   
        Slash,        
        Backslash,    
        Grave,        
        Equal,        
        Hyphen,       
        Space,        
        Enter,        
        Backspace,    
        Tab,          
        PageUp,       
        PageDown,     
        End,          
        Home,         
        Insert,       
        Delete,       
        Add,          
        Subtract,     
        Multiply,     
        Divide,       
        Left,         
        Right,        
        Up,           
        Down,         
        Numpad0,      
        Numpad1,      
        Numpad2,      
        Numpad3,      
        Numpad4,      
        Numpad5,      
        Numpad6,      
        Numpad7,      
        Numpad8,      
        Numpad9,      
        F1,           
        F2,           
        F3,           
        F4,           
        F5,           
        F6,           
        F7,           
        F8,           
        F9,           
        F10,          
        F11,          
        F12,          
        F13,          
        F14,          
        F15,          
        Pause,        
        
        KeyCount,     
    };

    struct KeyboardContext 
    {
        bool alt;
        bool shift;
        bool ctrl;

        Key key;
    };

    struct RenderTargetI 
    {
        /**
         * point -- левый верхний угол
         * size  -- размер ограничивающего прямоугольника
         * */

        virtual void setPixel(Vec2 pos, Color color) = 0;
        virtual void drawLine(Vec2 pos, Vec2 point1, Color color) = 0;
        virtual void drawRect(Vec2 pos, Vec2 size, Color color) = 0;
        virtual void drawEllipse(Vec2 pos, Vec2 size, Color color) = 0;
        virtual void drawTexture(Vec2 pos, Vec2 size, const Texture *texture) = 0;
        virtual void drawText(Vec2 pos, const char *content, uint16_t char_size, Color color) = 0;

        virtual Texture *getTexture() const = 0;
        virtual void setTexture(Texture *) = 0;

        /// как в RenderTexture::display
        virtual void display() = 0;

        /// clear
        virtual void clear() = 0;
        virtual void clear(Color color) = 0;
    };

    struct RenderableI 
    {
        virtual void render(RenderTargetI* texture) = 0;
        virtual ~RenderableI() = default;
    };

    struct Interface {
        virtual Array<const char *> getParamNames() const = 0;
        
        // в том же порядке, что getParamNames 
        virtual Array<double> getParams() const = 0;
        virtual void setParams(Array<double> params) = 0;

        virtual ~Interface() = default; 
    };

    struct Plugin {
        /* где-то тут лежит App*, но это дело автора плагина */
        uint64_t id;
        const char *name;
        InterfaceType type;

        virtual Interface *getInterface() const = 0;

        // плагин выбрали
        // [UPD]: только для системных
        virtual void selectPlugin() = 0;

        virtual ~Plugin() = default;
    };

    enum class EventType {
        MousePress,
        MouseRelease,
        MouseMove,
        KeyPress,
        KeyRelease,
	    Clock,
	    NumOfEvents
    };

    struct EventProcessableI 
    {
        // MouseContext хранит в себе координаты относительно позиции RT из GuiI::getRenderTarget.
        // Мотивация: если RT это не весь экран, а RT в каком-то окне (как идейно и планировалось), то, 
        // строго говоря, плагин не знает где в реальном мире находится RT (его могли перетаскивать и проч)
        // и не может пересчитать их в локальные.
        
	// true = перехватил, false = надо продолжать
        virtual bool onMouseMove(MouseContext context) = 0;
        virtual bool onMouseRelease(MouseContext context) = 0;
        virtual bool onMousePress(MouseContext context) = 0;
        virtual bool onKeyboardPress(KeyboardContext context) = 0;
        virtual bool onKeyboardRelease(KeyboardContext context) = 0;

        /// @brief clock event
        /// @param context microseconds
        virtual bool onClock(uint64_t delta) = 0;


	    virtual uint8_t getPriority() const = 0;

        virtual ~EventProcessableI() = default;
    };

    struct EventManagerI 
    {
        virtual void registerObject(EventProcessableI *object)   = 0;

        // 0 минимальный, ивенты приходят только объектам с их priority >= установленной по этому типу
        // 0 -- default
        virtual void setPriority(EventType, uint8_t priority)    = 0;
        virtual void unregisterObject(EventProcessableI *object) = 0;

        virtual ~EventManagerI() = default;
    };

    struct WidgetI 
    {
        virtual void registerSubWidget(WidgetI* object) = 0;
        virtual void unregisterSubWidget(WidgetI* object) = 0;

        virtual Vec2 getSize() const = 0;
        virtual void setSize(Vec2) = 0;

        virtual Vec2 getPos() const = 0;
        virtual void setPos(Vec2) = 0;

        virtual WidgetI *getParent() const = 0;
        virtual void setParent(WidgetI *root) = 0;

        virtual void move(Vec2 shift) = 0;

        // Жив ли виджет
        // Если true, то это идейно равносильно вызову деструктору, то есть его не надо рендерить, ему не надо передавать 
        // ивенты и тд и тп
        virtual bool getAvailable() const = 0;
        virtual void setAvailable(bool) = 0;

        virtual ~WidgetI() = default;
    };

    struct PluginWidgetI: public EventProcessableI, public RenderableI 
    {
        WidgetI* host;
    };

    struct ToolI : public Interface 
    {
        virtual const Texture *getIcon() const = 0;

        virtual void paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
        virtual void paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
        virtual void paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
        virtual void disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
    
        virtual ~ToolI() = default;
    };

    struct FilterI : public Interface 
    {
        virtual void apply(RenderTargetI *data) = 0;
        virtual ~FilterI() = default;
    };

    struct GuiI 
    {
        /**
         * @brief Get the root widget of widget tree
         * 
         * @return WidgetI* root
         */
        virtual WidgetI* getRoot() const = 0;

        /**
         * @brief Create a host WidgetI from PluginWidgetI and set `host` field in widget
         */
        virtual void createWidgetI(PluginWidgetI* widget) = 0;

        // плагин через это у хоста запрашивает, есть ли плагин c таким id. nullptr если нет
        virtual Plugin *queryPlugin(uint64_t id) = 0;

        // принимает имя файла
        // например, если у хоста все asset'ы этого плагина валяются в assets/shit/<filename>, то 
        // сюда надо передавать только filename
        virtual Texture *loadTextureFromFile(const char *filename) = 0;

        virtual ~GuiI() = default;
    };  

    struct App 
    {
        GuiI *root;
        EventManagerI *event_manager;
    };
}

extern "C" plugin::Plugin* getInstance(plugin::App *app);

#endif //SYM_STANDART