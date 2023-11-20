#ifndef SYM_WIDGET_I
#define SYM_WIDGET_I

#include "EventProcessableI.h"
#include "../Vec2/Vec2.h"
#include "RenderTargetI.h"

namespace plugin
{
    struct WidgetI: public EventProcessableI 
    {
        virtual void registerSubWidget(WidgetI* object) = 0;
        virtual void unregisterSubWidget(WidgetI* object) = 0;

        virtual plugin::Vec2 getSize() = 0;
        virtual void setSize(plugin::Vec2) = 0;

        virtual plugin::Vec2 getPos() = 0;
        virtual void setPos(plugin::Vec2) = 0;

        /// Нужно для обновления регинов.
        /// верно тогда и только тогда, когда виджет принадлежит плагину.
        /// В таком случае вызов getDefaultRegion невалиден (поэтому тут его и нет), и нужно 
        virtual bool isExtern() = 0;

        virtual void setParent(WidgetI *root) = 0;
        virtual WidgetI *getParent() = 0;

        virtual void move(plugin::Vec2 shift) = 0;

        // Жив ли виджет
        // Если true, то это идейно равносильно вызову деструктору, то есть его не надо рендерить, ему не надо передавать 
        // ивенты и тд и тп
        virtual bool getAvailable() = 0;
        virtual void setAvailable(bool) = 0;

        virtual void render(RenderTargetI* ) = 0;
        virtual void recalcRegion() = 0;

        virtual ~WidgetI() = 0;
    };
}

#endif //SYM_WIDGET_I