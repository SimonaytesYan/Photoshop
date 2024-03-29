#include "Curve.h"

extern "C" plugin::Plugin* getInstance(plugin::App *app)
{
    return new sym_plugin::CurvePlugin(app);
}

namespace sym_plugin
{
    CurvePlugin::CurvePlugin(plugin::App* app) :
    app (app)
    {
        filter = new CurveFilter(this);

        name = "SymCurve";
        type = plugin::InterfaceType::Filter;
    }

    void CurvePlugin::CreateCurveWindow(plugin::RenderTargetI* rt)
    {
        fprintf(stderr, "CreateCurveWindow\n");
        plugin::Vec2 start_pos = plugin::Vec2(600, 600);
        plugin::Vec2 size      = plugin::Vec2(400, 400);

        plugin::Vec2  button_size  = kButtonSize;
        plugin::Color button_color = plugin::Color(128, 128, 128);

        // Create functor

        ApplyFilterFunctor* functor = new ApplyFilterFunctor();
        functor->rt = rt;
        functor->r  = plugin::Array<uint8_t>(256, nullptr);
        functor->g  = plugin::Array<uint8_t>(256, nullptr);
        functor->b  = plugin::Array<uint8_t>(256, nullptr);

        for (int i = 0; i < 256; i++)
        {
            functor->r.data[i] = i;
            functor->g.data[i] = i;
            functor->b.data[i] = i;
        }

        // Create window

        CurveWindow* window = new CurveWindow(start_pos, size, functor, app);
        app->root->getRoot()->registerSubWidget(window->host);

        // Create OK button

        Button* ok_button = new Button(start_pos + plugin::Vec2((size - kButtonSize).x / 2,     
                                                                (size - kButtonSize).y * 11 / 12), 
                                       kButtonSize, kSelected, functor);
        app->root->createWidgetI(ok_button);
        ok_button->host->setPos(ok_button->getPos());
        ok_button->host->setSize(ok_button->getSize());
        

        Label* ok_label = new Label(ok_button->host->getPos() + plugin::Vec2(25, 0), 
                                    kTextSize, "OK", kTextColor);
        app->root->createWidgetI(ok_label);
        ok_label->host->setPos(ok_label->getPos());
        ok_label->host->setSize(ok_label->getSize());

        ok_button->host->registerSubWidget(ok_label->host);

        window->host->registerSubWidget(ok_button->host);
        functor->window = window;
    }

    plugin::Array<const char*> CurveFilter::getParamNames() const
    { 
        return {0, nullptr}; 
    }

    plugin::Array<double> CurveFilter::getParams() const
    { 
        return {0, nullptr}; 
    }

    void CurveFilter::setParams(plugin::Array<double> params)
    { }

    void CurveFilter::apply(plugin::RenderTargetI* rt)
    {
        parent->CreateCurveWindow(rt);
    }

    void CurveFilter::apply(plugin::RenderTargetI* rt, 
                            plugin::Array<uint8_t> r, 
                            plugin::Array<uint8_t> g, 
                            plugin::Array<uint8_t> b)
    {
        plugin::Texture* texture = rt->getTexture(); 
        plugin::Color*   pixels  = texture->pixels;

        for (int y = 0; y < texture->height; y++)
        {
            for (int x = 0; x < texture->width; x++)
            {
                plugin::Color* pixel_i = &pixels[y * texture->width + x];

                pixel_i->r = r.data[pixel_i->r];
                pixel_i->g = g.data[pixel_i->g];
                pixel_i->b = b.data[pixel_i->b];
            }
        }

        plugin::Vec2 pos(0, 0);
        plugin::Vec2 size(texture->width, texture->height);
        rt->drawTexture(pos, size, texture);

        delete texture;
    }

    //================================WIDGET====================================
    
    const double kPrecision = 1e-6;

    Widget::Widget (plugin::Vec2 _position, plugin::Vec2 _size) :
    position        (_position),
    size            (_size)
    {
    }

    Widget::~Widget()
    {
        host->setAvailable(false);
    }

    void Widget::move(plugin::Vec2 delta)
    {
        position = position + delta;
        host->move(delta);
    }

    void Widget::render(plugin::RenderTargetI* render_target)
    {
        size = host->getSize();
    }

    bool Widget::onKeyboardPress(plugin::KeyboardContext key)
    {
        return false;
    }

    bool Widget::onKeyboardRelease(plugin::KeyboardContext key)
    {
        return false;
    }

    bool Widget::onMousePress(plugin::MouseContext mouse)
    {
        fprintf(stderr, "(plugin) Widget::onMousePress %s(%p)\n", typeid(*this).name(), this);

        //if (InsideP(mouse.position))
        //    return true;
        return false;
    }
    
    bool Widget::onMouseRelease(plugin::MouseContext mouse)
    {
        return false;
    }

    bool Widget::onMouseMove(plugin::MouseContext mouse)
    {
        return false;
    }

    bool Widget::onClock(size_t delta)
    {
        return false;
    }

    bool Widget::InsideP(plugin::Vec2 v)
    {
        return v.GetX() - position.GetX() >= -kPrecision &&
               v.GetX() - position.GetX() <= size.GetX() + kPrecision &&
               v.GetY() - position.GetY() >= -kPrecision && 
               v.GetY() - position.GetY() <= size.GetY() + kPrecision;
    }

    struct ButtonMove : ButtonFunction
    {
        CurveWindow* window;
        plugin::Vec2 last_mouse_pos;

        ButtonMove() {}
        ButtonMove(CurveWindow* window) : 
        window (window),
        last_mouse_pos (plugin::Vec2())
        {}

        void operator()() override
        {
            window->SetMoving(true);
        }
    };

    struct ButtonClose : ButtonFunction
    {
        CurveWindow* window;

        ButtonClose() {}
        ButtonClose(CurveWindow* window) : 
        window (window) 
        {}

        void operator()() override
        {
            window->Close();
        }
    };

    //===============================CURVE WINDOW===============================

    CurveWindow::CurveWindow(plugin::Vec2 pos, plugin::Vec2 size, ApplyFilterFunctor* functor, plugin::App* app) :
    Widget             (pos, size),
    points_r           (List<plugin::Vec2>(0)),
    points_g           (List<plugin::Vec2>(0)),
    points_b           (List<plugin::Vec2>(0)),
    functor            (functor),
    app                (app),
    moving             (false),
    moving_point_index (-1)
    {
        app->root->createWidgetI(this);
        host->setPos(position);
        host->setSize(size);

        priority = 255;

        graph_size = plugin::Vec2(255, 255);
        graph_pos  = plugin::Vec2(pos + (size - graph_size) / 2);

        plugin::Vec2 p0(graph_pos.GetX(), graph_pos.GetY() + graph_size.GetY());
        plugin::Vec2 p1(graph_pos.GetX() + graph_size.GetX(), graph_pos.GetY());

        points_r.PushBack(p0);
        points_r.PushBack(p1);
            
        points_g.PushBack(p0);
        points_g.PushBack(p1);

        points_b.PushBack(p0);
        points_b.PushBack(p1);

        // Button to move window
        Button* header_button = new Button(position, plugin::Vec2(size.x - 25, 25), 
                                           plugin::Color(235,235,235), new ButtonMove(this));
        app->root->createWidgetI(header_button);
        header_button->host->setPos(header_button->getPos());
        header_button->host->setSize(header_button->getSize());

        Label* header_label = new Label(position, kTextSize, "Curve filter", kTextColor);
        app->root->createWidgetI(header_label);
        header_label->host->setPos(header_label->getPos());
        header_label->host->setSize(header_label->getSize());
        
        // Header
        header_button->host->registerSubWidget(header_label->host);
        host->registerSubWidget(header_button->host);

        // Close button window
        plugin::Vec2 close_button_pos = plugin::Vec2(position.GetX() + size.GetX() - 25, 
                                                     position.GetY());
        Button* close_button = new Button(close_button_pos, plugin::Vec2(25, 25), 
                                          plugin::Color(217, 217, 217),
                                          nullptr, new ButtonClose(this));
        app->root->createWidgetI(close_button);
        close_button->host->setPos(close_button->getPos());
        close_button->host->setSize(close_button->getSize());

        Label* close_label = new Label(close_button_pos + plugin::Vec2(9, 1), 
                                       kTextSize - 5, "X", kTextColor);
        app->root->createWidgetI(close_label);
        close_label->host->setPos(close_label->getPos());
        close_label->host->setSize(close_label->getSize());

        close_button->host->registerSubWidget(close_label->host);
        host->registerSubWidget(close_button->host);                    

        // Add button to switch color

        ChangeStatusFunctor* red_button_functor   = new ChangeStatusFunctor(CurveWindowStatus::Red,   this);
        ChangeStatusFunctor* green_button_functor = new ChangeStatusFunctor(CurveWindowStatus::Green, this);
        ChangeStatusFunctor* blue_button_functor  = new ChangeStatusFunctor(CurveWindowStatus::Blue,  this);

        red_button   = new Button(host->getPos() + plugin::Vec2(20, 30), 
                                  kButtonSize, kUnSelected, red_button_functor);
        green_button = new Button(host->getPos() + plugin::Vec2(160, 30), 
                                  kButtonSize, kUnSelected, green_button_functor);
        blue_button  = new Button(host->getPos() + plugin::Vec2(300, 30), 
                                  kButtonSize, kUnSelected, blue_button_functor);
        app->root->createWidgetI(red_button);
        app->root->createWidgetI(green_button);
        app->root->createWidgetI(blue_button);

        red_button  ->host->setPos(red_button  ->getPos());
        green_button->host->setPos(green_button->getPos());
        blue_button ->host->setPos(blue_button ->getPos());

        red_button  ->host->setSize(red_button  ->getSize());
        green_button->host->setSize(green_button->getSize());
        blue_button ->host->setSize(blue_button ->getSize());

        Label* red_label   = new Label(red_button->host->getPos(), kTextSize, "Red",   kTextColor);
        Label* green_label = new Label(green_button->host->getPos(), kTextSize, "Green", kTextColor);
        Label* blue_label  = new Label(blue_button->host->getPos(), kTextSize, "Blue",  kTextColor);

        app->root->createWidgetI(red_label);
        app->root->createWidgetI(green_label);
        app->root->createWidgetI(blue_label);

        red_label  ->host->setPos(red_label  ->getPos());
        green_label->host->setPos(green_label->getPos());
        blue_label ->host->setPos(blue_label ->getPos());

        red_label  ->host->setSize(red_label  ->getPos());
        green_label->host->setSize(green_label->getPos());
        blue_label ->host->setSize(blue_label ->getPos());

        red_button  ->host->registerSubWidget(red_label  ->host);
        green_button->host->registerSubWidget(green_label->host);
        blue_button ->host->registerSubWidget(blue_label ->host);

        host->registerSubWidget(red_button  ->host);
        host->registerSubWidget(green_button->host);
        host->registerSubWidget(blue_button ->host);

        SetStatus(CurveWindowStatus::Red);
    }

    void CurveWindow::move(plugin::Vec2 delta)
    {
        graph_pos = graph_pos + delta;
        
        for (int index = points_r.Begin(); index != -1; index = points_r.Iterate(index))
            points_r[index].val = delta + points_r[index].val;
        for (int index = points_g.Begin(); index != -1; index = points_g.Iterate(index))
            points_g[index].val = delta + points_g[index].val;
        for (int index = points_b.Begin(); index != -1; index = points_b.Iterate(index))
            points_b[index].val = delta + points_b[index].val;

        Widget::move(delta);
    }

    void CurveWindow::AddPoint(List<plugin::Vec2>& points, plugin::Vec2 position)
    {
        if (position.x < graph_pos.x                ||
            position.x > graph_pos.x + graph_size.x ||
            position.y < graph_pos.y                ||
            position.y > graph_pos.y + graph_size.y)
        return;

        int p0 = points.Begin();
        for (int p1 = points.Iterate(p0); p1 != -1; p1 = points.Iterate(p1))
        {
            if (points[p0].val.x < position.x && position.x < points[p1].val.x)
            {
                points.Insert(position, p0);
                
                // If curve intersect frame point dont be added 
                if (DrawUsingCatMullRom_plugin(nullptr, plugin::Color(0, 0, 0), 0, 
                                               points, graph_pos, graph_size))
                {
                    points.Remove(points[p0].next);
                    return;
                }
                
                moving_point_index = points[p0].next;
                break;
            }
            p0 = p1;
        }
    }

    void CurveWindow::ProcessPoint(List<plugin::Vec2>& points, plugin::Vec2 position)
    {
        for (int p0 = points.Begin(); p0 != -1; p0 = points.Iterate(p0))
        {
            if ((points[p0].val - position).Length() < kCurvePointSize)
            {
                moving_point_index = p0;
                return;
            }
        }

        AddPoint(points, position);
    }

    bool CurveWindow::onMousePress(plugin::MouseContext mouse)
    {
        fprintf(stderr, "(plugin) CurveWindow::onMousePress (%p)\n", this);

        if (InsideP(mouse.position))
        {
            fprintf(stderr, "(plugin) press inside curve window (%lg, %lg)\n", mouse.position.x, mouse.position.y);

            switch (status)
            {
                case CurveWindowStatus::Red:
                    ProcessPoint(points_r, mouse.position);
                    break;
                case CurveWindowStatus::Green:
                    ProcessPoint(points_g, mouse.position);
                    break;
                case CurveWindowStatus::Blue:
                    ProcessPoint(points_b, mouse.position);
                    break;
                
                default:
                    fprintf(stderr, "(plugin) CurveWindow::onMousePress status = %d\n", status);
                    break;
            }

            return true;
        }

        return false;
    }

    void CurveWindow::MovePoint(plugin::Vec2 mouse_pos)
    {
        if (moving_point_index != -1)
        {
            List<plugin::Vec2>* points;

            switch (status)
            {
                case CurveWindowStatus::Red:
                    points = &points_r;
                    break;
                case CurveWindowStatus::Green:
                    points = &points_g;
                    break;
                case CurveWindowStatus::Blue:
                    points = &points_b;
                    break;
                
                default:
                    break;
            }

            // Check going abroad
            if (mouse_pos.x < graph_pos.x)
                mouse_pos.x = graph_pos.x;
            if (mouse_pos.y < graph_pos.y)
                mouse_pos.y = graph_pos.y;
            
            if (mouse_pos.x > graph_pos.x + graph_size.x)
                mouse_pos.x = graph_pos.x + graph_size.x;
            if (mouse_pos.y > graph_pos.y + graph_size.y)
                mouse_pos.y = graph_pos.y + graph_size.y;
            

            // First and last points dont move horizontal
            if (moving_point_index == points->Begin() || 
                moving_point_index == points->End  ())
                mouse_pos.x = (*points)[moving_point_index].val.x;
            else
            {
                plugin::Vec2 next_point = (*points)[points->Iterate(moving_point_index)].val;
                plugin::Vec2 prev_point = (*points)[points->Deterate(moving_point_index)].val;

                mouse_pos.x = min(mouse_pos.x, next_point.x);
                mouse_pos.x = max(mouse_pos.x, prev_point.x);
            }

            //(*points)[moving_point_index].val = mouse_pos;
            
            // Checking if curve going abroad
            plugin::Vec2 old_value = (*points)[moving_point_index].val;
            (*points)[moving_point_index].val = mouse_pos;

            if (DrawUsingCatMullRom_plugin(nullptr, plugin::Color(0, 0, 0), 0, 
                                           *points, graph_pos, graph_size))
                (*points)[moving_point_index].val = old_value;
            else
                (*points)[moving_point_index].val = mouse_pos;
        }
    }

    bool CurveWindow::onMouseMove(plugin::MouseContext mouse)
    {
        MovePoint(mouse.position);

        if (moving)
        {
            if (!(last_mouse_pos == plugin::Vec2(0, 0)))
            {
                move(mouse.position - last_mouse_pos);
            }
            last_mouse_pos = mouse.position;
        }

        return false;
    }

    bool CurveWindow::onMouseRelease(plugin::MouseContext mouse)
    {
        if (Widget::onMouseRelease(mouse))
            return true;

        moving_point_index = -1;
        moving             = false;
        last_mouse_pos     = plugin::Vec2(0, 0);

        return false;
    }

    CurveWindow::~CurveWindow()
    {
    }

    plugin::Color GetPixel(plugin::Texture* texture, plugin::Vec2 current_point)
    {
        return texture->pixels[(int)current_point.y * texture->width + (int)current_point.x];
    }

    void CurveWindow::UpdateFilter(plugin::Texture* texture)
    {
        plugin::Color           status_color;
        plugin::Array<uint8_t> *status_array;
        List<plugin::Vec2>     *points;

        switch (status)
        {
            case CurveWindowStatus::Red:
                status_color = kCurveColorR;
                status_array = &functor->r;
                points       = &points_r;
                break;
            case CurveWindowStatus::Green:
                status_color = kCurveColorG;
                status_array = &functor->g;
                points       = &points_g;
                break;
            case CurveWindowStatus::Blue:
                status_color = kCurveColorB;
                status_array = &functor->b;
                points       = &points_b;
                break;

            default:
                break;
        }

        plugin::Vec2 point(graph_pos); 
        for (int i = 0; i < 256; i++)
        {
            plugin::Vec2 current_point = point;
            while (current_point.y <= graph_pos.y + graph_size.y &&
                   ((GetPixel(texture, current_point).r != status_color.r) || 
                    (GetPixel(texture, current_point).g != status_color.g) || 
                    (GetPixel(texture, current_point).b != status_color.b)))
            {
                current_point.y++;
            }

            if (current_point.y <= graph_pos.y + graph_size.y)
            {
                status_array->data[i] = 255 - (current_point.y - graph_pos.y);
            }
            point.x++;
        }

        delete texture;
    }

    void CurveWindow::DrawCurve(plugin::RenderTargetI* target, 
                                List<plugin::Vec2> &points, 
                                plugin::Color color)
    {
        plugin::Vec2 left_up    = graph_pos;
        plugin::Vec2 right_down = graph_pos + graph_size;
        plugin::Vec2 left_down  = graph_pos + plugin::Vec2(0, graph_size.y);
        plugin::Vec2 right_up   = graph_pos + plugin::Vec2(graph_size.x, 0);

        target->drawLine(left_up,    left_down, plugin::Color(0, 0, 0));
        target->drawLine(left_up,    right_up,  plugin::Color(0, 0, 0));
        target->drawLine(right_down, left_down, plugin::Color(0, 0, 0));
        target->drawLine(right_down, right_up,  plugin::Color(0, 0, 0));
       
        plugin::Vec2 point_size = plugin::Vec2(kCurvePointSize, kCurvePointSize);

        for (int index = points.Begin(); index != -1; index = points.Iterate(index))
        {
            target->drawEllipse(points[index].val - point_size / 2 + plugin::Vec2(kThickness, kThickness) / 2, 
                                point_size, color);            
        }

        DrawUsingCatMullRom_plugin(target, color, kThickness, points, graph_pos, graph_size);
    }

    void CurveWindow::render(plugin::RenderTargetI* target)
    {
        Widget::render(target);
        target->drawRect(position, size, kBackgroundColor);

        switch (status)
        {
            case CurveWindowStatus::Red:
                DrawCurve(target, points_r, kCurveColorR);
                break;
            case CurveWindowStatus::Green:
                DrawCurve(target, points_g, kCurveColorG);
                break;
            case CurveWindowStatus::Blue:
                DrawCurve(target, points_b, kCurveColorB);
                break;
        
            default:
                fprintf(stderr, "CurveWindow::render status = %d\n", status);
                break;
        }

        UpdateFilter(target->getTexture());
        
    }

    //===============================BUTTON=====================================

    void Button::render(plugin::RenderTargetI* render_target)
    {
        Widget::render(render_target);

        if (pressed)
        {
            plugin::Color inverse_color(255 - background_color.r,
                                        255 - background_color.g,
                                        255 - background_color.b); 
            render_target->drawRect(position, size, inverse_color);
        }
        else
            render_target->drawRect(position, size, background_color);
    }

    bool Button::onMousePress(plugin::MouseContext mouse)
    {
        fprintf(stderr, "(plugin) Button::onMousePress (%p)\n", this);
        if (InsideP(mouse.position))
        {
            if (Widget::onMousePress(mouse))
                return true;

            pressed = true;
            if (on_press == nullptr)
                return false;

            (*on_press)();      // call button function

            return true;
        }
        
        return false;
    }

    bool Button::onMouseRelease(plugin::MouseContext mouse)
    {
        if (InsideP(mouse.position))
        {
            bool intercepted = Widget::onMouseRelease(mouse);

            if (!intercepted)
            {
                pressed = false;
                if (on_release == nullptr)
                    return false;

                (*on_release)();
            }

            return true;
        }
        
        return false;
    }

    bool Button::onMouseMove(plugin::MouseContext mouse)
    {
        if (!InsideP(mouse.position))
            pressed = false;

        return false;
    }

    //====================================LABEL=================================

    Label::Label(plugin::Vec2 _position, int _character_size, 
                const char* _text, plugin::Color _text_color) :
    Widget(_position, plugin::Vec2(strlen(_text) * (_character_size - 5), (_character_size + 10))),
    character_size (_character_size),
    text_color     (_text_color)
    {
        text = new char[strlen(_text) + 1];
        strcpy(text, _text);
    }

    Label::~Label()
    {
        delete[] text;
    }

    void Label::SetText(const char* new_text)
    {
        free(text);
        text = (char*)calloc(sizeof(char), strlen(new_text) + 1);
        strcpy(text, new_text);
    }

    void Label::render(plugin::RenderTargetI* render_target)
    {
        Widget::render(render_target);

        render_target->drawText(position, text, character_size, text_color);
    }

    //==================================FUNCTORS================================

    void ApplyFilterFunctor::operator()()
    {
        window->host->setAvailable(false);

        filter->apply(rt, r, g, b);
    }
}