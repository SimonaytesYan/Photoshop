#ifndef SYM_RENDER_TARGET_I
#define SYM_RENDER_TARGET_I

#include <cstdint>

#include "../Color.h"
#include "../Vec2/Vec2.h"
#include "../Texture/Texture.h"

namespace plugin
{
    struct RenderTargetI 
    {
        /**
         * point -- левый верхний угол
         * size  -- размер ограничивающего прямоугольника
         * */

        virtual void setPixel(plugin::Vec2 pos, plugin::Color color) = 0;
        virtual void drawLine(plugin::Vec2 pos, plugin::Vec2 point1, plugin::Color color) = 0;
        virtual void drawRect(plugin::Vec2 pos, plugin::Vec2 size, plugin::Color color) = 0;
        virtual void drawEllipse(plugin::Vec2 pos, plugin::Vec2 size, plugin::Color color) = 0;
        virtual void drawTexture(plugin::Vec2 pos, plugin::Vec2 size, const plugin::Texture *texture) = 0;
        virtual void drawText(plugin::Vec2 pos, const char *content, uint16_t char_size, plugin::Color color) = 0;

        virtual Texture *getTexture() = 0;

        /// как в RenderTexture::display
        virtual void display() = 0;

        /// clear
        virtual void clear() = 0;
    };
}

#endif //SYM_RENDER_TARGET_I