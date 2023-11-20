#ifndef SYM_RENDER_TARGET_I
#define SYM_RENDER_TARGET_I

#include <cstdint>

#include "../Color.h"
#include "../Vec2/Vec2.h"
#include "../Texture/Texture.h"

namespace plugin
{
    struct RenderTargetI {
        /**
         * point -- левый верхний угол
         * size  -- размер ограничивающего прямоугольника
         * */

        virtual void setPixel(Vec2 pos, Color color) = 0;
        virtual void drawLine(Vec2 pos, Vec2 point1, Color color) = 0;
        virtual void drawRect(Vec2 pos, Vec2 size, Color color) = 0;
        virtual void drawEllipse(Vec2 pos, Vec2 size, Color color) = 0;
        virtual void drawTexture(Vec2 pos, Vec2 size, const plugin::Texture *texture) = 0;
        virtual void drawText(Vec2 pos, const char *content, uint16_t char_size, Color color) = 0;

        virtual Texture *getTexture() = 0;

        /// как в RenderTexture::display
        virtual void display() = 0;

        /// clear
        virtual void clear() = 0;
    };
}

#endif //SYM_RENDER_TARGET_I