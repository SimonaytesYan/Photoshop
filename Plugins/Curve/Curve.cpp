#include "Curve.h"

extern "C" plugin::Plugin* getInstance(plugin::App *app)
{
    return new sym_plugin::CurvePlugin(app);
}

namespace sym_plugin
{
    const plugin::Color kBackgroundColor(150, 100, 100);


    CurvePlugin::CurvePlugin(plugin::App* app) :
    app (app)
    {
        filter = new CurveFilter(this);

        name = "SymCurve";
        type = plugin::InterfaceType::Filter;
    }

    void CurvePlugin::CreateCurveWindow(plugin::RenderTargetI* rt)
    {        
        plugin::Vec2 start_pos = plugin::Vec2(100, 100);
        plugin::Vec2 size      = plugin::Vec2(800, 800);

        plugin::Vec2  button_size  = plugin::Vec2(100, 50);
        plugin::Color button_color = plugin::Color(128, 128, 128);

        // Create OK button

        ApplyFilterFunctor* functor = new ApplyFilterFunctor();
        functor->rt = rt;
        functor->r  = plugin::Array<uint8_t>(255);
        functor->r.data = new uint8_t[255];
        functor->g  = plugin::Array<uint8_t>(255);
        functor->g.data = new uint8_t[255];
        functor->b  = plugin::Array<uint8_t>(255);
        functor->b.data = new uint8_t[255];

        Button* ok_button = new Button(start_pos + plugin::Vec2(300, 650), 
                                       plugin::Vec2(100, 50), 
                                       plugin::Color(128, 128, 128), 
                                       functor);
        Label* ok_label = new Label(ok_button->getSize(), 10, "OK", 
                                               plugin::Color(0, 255, 255));

        ok_button->registerSubWidget(ok_label);
        
        // Create window

        CurveWindow* window = new CurveWindow(start_pos, size, functor, app);

        window->registerSubWidget(ok_button);
        functor->window = window;
        
        // Make it modal
        window->setPriority(255);
        app->event_manager->registerObject(window);
        app->event_manager->setPriority(plugin::EventType::MousePress, 
                                        255);

        app->root->getRoot()->registerSubWidget(window);
    }

    plugin::Array<const char*> CurveFilter::getParamNames()
    { 
        return {0, nullptr}; 
    }

    plugin::Array<double> CurveFilter::getParams()
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


        plugin::Vec2 pos  = {0, 0};
        plugin::Vec2 size = {texture->width, texture->height};
        rt->drawTexture(pos, size, texture);

        delete[] texture->pixels;
        delete texture;
    }

    //================================WIDGET====================================
    
    const double kPrecision = 1e-6;

    Widget::Widget (plugin::Vec2 _position, plugin::Vec2 _size, bool _available) :
    available       (_available),
    position        (_position),
    size            (_size),
    sub_widgets     (List<plugin::WidgetI*>(0)),
    parent          (nullptr)
    {
    }

    Widget::~Widget()
    {
        for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
            delete sub_widgets[i].val;
        
        if (parent != nullptr)
            parent->unregisterSubWidget(this);
    }

    void Widget::move(plugin::Vec2 delta)
    {
        for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
            sub_widgets[i].val->move(delta);
    }

    void Widget::unregisterSubWidget(WidgetI* son)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
        {
            if (sub_widgets[index].val == son)
            {
                sub_widgets.Remove(index);
                break;
            }
        }
    }

    void Widget::render(plugin::RenderTargetI* render_target)
    {
        if (available)
        {
            for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
            {
                plugin::WidgetI* sub_widget = sub_widgets[index].val;
                if (sub_widget->getAvailable())
                        sub_widget->render(render_target);
            }
        }
    }

    void Widget::registerSubWidget(WidgetI* new_widget)
    {
        new_widget->setParent(this);
        sub_widgets.PushBack(new_widget);

        if (parent != nullptr)
            parent->recalcRegion();
    }

    bool WidgetEventRound(Events event, void*  event_args, 
                          List<plugin::WidgetI*> &objects, bool available)
    {
        if (!available)
            return false;

        bool intercepted = false;
        int index        = objects.End();
        while (index != -1)
        {
            switch (event)
            {
            case KEY_PRESS:
                intercepted = objects[index].val->onKeyboardPress(*(plugin::KeyboardContext*)event_args);
                break;
            case KEY_RELEASE:
                intercepted = objects[index].val->onKeyboardRelease(*(plugin::KeyboardContext*)event_args);
                break;
            case MOUSE_PRESS:
                intercepted = objects[index].val->onMousePress(*(plugin::MouseContext*)event_args);
                break;
            case MOUSE_RELEASE:
                intercepted = objects[index].val->onMouseRelease(*(plugin::MouseContext*)event_args);
                break;
            case MOUSE_MOVE:
                intercepted = objects[index].val->onMouseMove(*(plugin::MouseContext*)event_args);
                break;
            case ON_CLOCK:
                intercepted = objects[index].val->onClock(*(size_t*)event_args);
                break;
            
            default:
                break;
            }
            if (intercepted)
                break;
            index = objects.Deterate(index);
        }

        return intercepted;
    }

    bool Widget::onKeyboardPress(plugin::KeyboardContext key)
    {
        return WidgetEventRound(KEY_PRESS, &key, sub_widgets, available);
    }

    bool Widget::onKeyboardRelease(plugin::KeyboardContext key)
    {
        return WidgetEventRound(KEY_RELEASE, &key, sub_widgets, available);
    }

    bool Widget::onMousePress(plugin::MouseContext mouse)
    {
        if (InsideP(mouse.position))
            return WidgetEventRound(MOUSE_PRESS, &mouse, sub_widgets, available);
        return false;
    }
    
    bool Widget::onMouseRelease(plugin::MouseContext mouse)
    {
        return WidgetEventRound(MOUSE_RELEASE, &mouse, sub_widgets, available);
    }

    bool Widget::onMouseMove(plugin::MouseContext mouse)
    {
        return WidgetEventRound(MOUSE_MOVE, &mouse, sub_widgets, available);
    }

    bool Widget::onClock(size_t delta)
    {
        return WidgetEventRound(ON_CLOCK, &delta, sub_widgets, available);
    }

    void Widget::recalcRegion()
    {
    }

    bool Widget::InsideP(plugin::Vec2 v)
    {
        return v.GetX() - position.GetX() >= -kPrecision &&
               v.GetX() - position.GetX() <= size.GetX() + kPrecision &&
               v.GetY() - position.GetY() >= -kPrecision && 
               v.GetY() - position.GetY() <= size.GetY() + kPrecision;
    }

    //===============================CURVE WINDOW==============================

    CurveWindow::CurveWindow(plugin::Vec2 pos, plugin::Vec2 size, ApplyFilterFunctor* functor, plugin::App* app) :
    Widget             (pos, size),
    points_r           (List<plugin::Vec2>(0)),
    points_g           (List<plugin::Vec2>(0)),
    points_b           (List<plugin::Vec2>(0)),
    functor            (functor),
    app                (app),
    moving_point_index (-1)
    {
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


         // Add button to switch color

        ChangeStatusFunctor* red_button_functor   = new ChangeStatusFunctor(CurveWindowStatus::Red,   this);
        ChangeStatusFunctor* green_button_functor = new ChangeStatusFunctor(CurveWindowStatus::Green, this);
        ChangeStatusFunctor* blue_button_functor  = new ChangeStatusFunctor(CurveWindowStatus::Blue,  this);

        plugin::Vec2 button_size(100, 50); 

        red_button   = new Button(getPos() + plugin::Vec2(100, 50), 
                                  button_size, kUnSelected, red_button_functor);
        green_button = new Button(getPos() + plugin::Vec2(300, 50), 
                                  button_size, kUnSelected, green_button_functor);
        blue_button  = new Button(getPos() + plugin::Vec2(500, 50), 
                                  button_size, kUnSelected, blue_button_functor);

        registerSubWidget(red_button);
        registerSubWidget(green_button);
        registerSubWidget(blue_button);

        SetStatus(CurveWindowStatus::Red);
    }

    void CurveWindow::AddPoint(List<plugin::Vec2>& points, plugin::Vec2 position)
    {
        int p0 = points.Begin();
        for (int p1 = points.Iterate(p0); p1 != -1; p1 = points.Iterate(p1))
        {
            if (points[p0].val.x < position.x && position.x < points[p1].val.x)
            {
                points.Insert(position, p0);
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
        if (Widget::onMousePress(mouse))
            return true;
        
        if (available && InsideP(mouse.position))
        {
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
                    fprintf(stderr, "CurveWindow::onMousePress status = %d\n", status);
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
            if (mouse_pos.x < position.x)
                mouse_pos.x = position.x;
            if (mouse_pos.y < position.y)
                mouse_pos.y = position.y;
            
            if (mouse_pos.x > position.x + size.x)
                mouse_pos.x = position.x + size.x;
            if (mouse_pos.y > position.y + size.y)
                mouse_pos.y = position.y + size.y;

            (*points)[moving_point_index].val = mouse_pos;
        }
    }

    bool CurveWindow::onMouseMove(plugin::MouseContext mouse)
    {
        if (Widget::onMouseMove(mouse))
            return true;

        MovePoint(mouse.position);

        return false;
    }

    bool CurveWindow::onMouseRelease(plugin::MouseContext mouse)
    {
        if (Widget::onMouseRelease(mouse))
            return true;

        moving_point_index = -1;

        return false;
    }

    CurveWindow::~CurveWindow()
    {
        app->event_manager->unregisterObject(this);
        app->event_manager->setPriority(plugin::EventType::MouseMove, 0);
        app->event_manager->setPriority(plugin::EventType::MousePress, 0);
        app->event_manager->setPriority(plugin::EventType::MouseRelease, 0);
    }

    void CurveWindow::DrawCurve(plugin::RenderTargetI* target, 
                                List<plugin::Vec2> &points, 
                                plugin::Color color)
    {
        plugin::Vec2 point_size = plugin::Vec2(kCurvePointSize, kCurvePointSize);

        target->drawRect(position, size, plugin::Color(100, 100, 100));
        int p0 = points.Begin();
        for (int p1 = points.Iterate(p0); p1 != -1; p1 = points.Iterate(p1))
        {
            target->drawLine(points[p0].val, points[p1].val, color);

            target->drawEllipse(points[p0].val - point_size / 2, 
                                point_size, color);
            p0 = p1;
        }
        target->drawEllipse(points[p0].val - point_size / 2, 
                            point_size, color);
    }

    void CurveWindow::render(plugin::RenderTargetI* target)
    {
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
        
        Widget::render(target);
    }

    //===============================BUTTON=====================================

    void Button::render(plugin::RenderTargetI* render_target)
    {
        if (available)
        {
                if (pressed)
                    render_target->drawRect(position, size, background_color.Inverse());
                else
                    render_target->drawRect(position, size, background_color);

            Widget::render(render_target);
        }
    }

    bool Button::onMousePress(plugin::MouseContext mouse)
    {
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
        {
            pressed = false;
        }
        return false;
    }

    //====================================LABEL=================================

    Label::Label(plugin::Vec2 _position, int _character_size, 
                const char* _text, plugin::Color _background, plugin::Color _text_color) :
    Widget(_position, plugin::Vec2(strlen(_text) * (_character_size - 5), (_character_size + 10))),
    character_size (_character_size),
    background     (_background),
    text_color     (_text_color)
    {
        text = (char*)calloc(sizeof(char), strlen(_text) + 1);
        strcpy(text, _text);
    }

    Label::~Label()
    {
        free(text);
    }

    void Label::SetText(const char* new_text)
    {
        free(text);
        text = (char*)calloc(sizeof(char), strlen(new_text) + 1);
        strcpy(text, new_text);
    }

    void Label::render(plugin::RenderTargetI* render_target)
    {
        if (available)
        {
            //render_target->drawRect(position, size, background);
            render_target->drawText(position, text, character_size, text_color);

            Widget::render(render_target);
        }
    }

    //==================================FUNCTORS================================

    void ApplyFilterFunctor::operator()()
    {
        delete window;
        filter->apply(rt, r, g, b);
    }
}