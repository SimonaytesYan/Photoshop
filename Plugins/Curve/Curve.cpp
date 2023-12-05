#include "Curve.h"

namespace sym_plugin
{
    const plugin::Color kBackgroundColor(150, 100, 100);

    extern "C" plugin::Plugin* getInstance(plugin::App *app)
    {
        return new CurvePlugin(app);
    }

    CurvePlugin::CurvePlugin(plugin::App* app) :
    app (app)
    { 
        filter = new CurveFilter(this);

        name = "SymCurve";
        type = plugin::InterfaceType::Filter;
    }

    void CurvePlugin::CreateCurveWindow(plugin::RenderTargetI* rt)
    {
        // Create window
        plugin::Vec2 start_pos = plugin::Vec2(100, 100);
        plugin::Vec2 size      = plugin::Vec2(800, 800);
        CurveWindow* window    = new CurveWindow(start_pos, size);
        
        // Make it modal
        window->setPriority(255);
        app->event_manager->registerObject(window);
        app->event_manager->setPriority(plugin::EventType::MouseMove, 
                                        window->getPriority());
        app->event_manager->setPriority(plugin::EventType::MousePress, 
                                        window->getPriority());
        app->event_manager->setPriority(plugin::EventType::MouseRelease, 
                                        window->getPriority());
        
        // Add OK button

        ApplyFilterFunctor* functor = new ApplyFilterFunctor();
        functor->rt = rt;
        functor->r  = plugin::Array<uint8_t>(255);
        functor->g  = plugin::Array<uint8_t>(255);
        functor->b  = plugin::Array<uint8_t>(255);

        window->registerSubWidget(new Button(start_pos + plugin::Vec2(300, 650), 
                                             plugin::Vec2(100, 50), 
                                             plugin::Color(128, 128, 128), 
                                             functor));
        
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
    sub_widgets     (List<WidgetPtr>(0)),
    parent          (nullptr)
    {
    }

    Widget::~Widget()
    {
    }

    void Widget::move(plugin::Vec2 delta)
    {
        for (int i = sub_widgets.Begin(); i != -1; i = sub_widgets.Iterate(i))
            sub_widgets[i].val.move(delta);
    }

    void Widget::unregisterSubWidget(WidgetI* son)
    {
        for (int index = sub_widgets.Begin(); index != -1; index = sub_widgets.Iterate(index))
        {
            if (sub_widgets[index].val.is_extern && 
                sub_widgets[index].val.widget_i == son ||
                !sub_widgets[index].val.is_extern && 
                sub_widgets[index].val.widget   == son)
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
                WidgetPtr sub_widget = sub_widgets[index].val;
                if (sub_widget.getAvailable())
                {
                    if (sub_widget.is_extern)
                        sub_widget.widget_i->render(render_target);
                    else
                        sub_widget.widget->render(render_target);
                }
            }
        }
    }

    void Widget::registerSubWidget(WidgetI* new_widget)
    {
        new_widget->setParent(this);
        sub_widgets.PushBack(WidgetPtr(new_widget));

        parent->recalcRegion();
    }

    bool WidgetEventRound(Events event, void*  event_args, 
                        List<WidgetPtr> &objects, bool available)
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
                intercepted = objects[index].val.onKeyboardPress(*(plugin::KeyboardContext*)event_args);
                break;
            case KEY_RELEASE:
                intercepted = objects[index].val.onKeyboardRelease(*(plugin::KeyboardContext*)event_args);
                break;
            case MOUSE_PRESS:
                intercepted = objects[index].val.onMousePress(*(plugin::MouseContext*)event_args);
                break;
            case MOUSE_RELEASE:
                intercepted = objects[index].val.onMouseRelease(*(plugin::MouseContext*)event_args);
                break;
            case MOUSE_MOVE:
                intercepted = objects[index].val.onMouseMove(*(plugin::MouseContext*)event_args);
                break;
            case ON_CLOCK:
                intercepted = objects[index].val.onClock(*(size_t*)event_args);
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
        if (!available)
            return;
        
        if (parent != nullptr)
            parent->recalcRegion();
    }

    bool Widget::InsideP(plugin::Vec2 v)
    {
        return v.GetX() - position.GetX() >= -kPrecision &&
               v.GetX() - position.GetX() <= size.GetX() + kPrecision &&
               v.GetY() - position.GetY() >= -kPrecision && 
               v.GetY() - position.GetY() <= size.GetY() + kPrecision;
    }

    //===============================RENDER WINDOW==============================

    void CurveWindow::render(plugin::RenderTargetI* target)
    {
        rt->display();
        target->drawTexture(position, size, rt->getTexture());

        Widget::render(target);
    }
}