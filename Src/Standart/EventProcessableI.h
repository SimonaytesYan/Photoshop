#ifndef SYM_EVENT_PROCESSABLE_I
#define SYM_EVENT_PROCESSABLE_I

#include <cstdint>
#include "../Keys.h"

namespace plugin
{
    struct EventProcessableI 
    {
        // plugin::MouseContext хранит в себе координаты относительно позиции RT из GuiI::getRenderTarget.
        // Мотивация: если RT это не весь экран, а RT в каком-то окне (как идейно и планировалось), то, 
        // строго говоря, плагин не знает где в реальном мире находится RT (его могли перетаскивать и проч)
        // и не может пересчитать их в локальные.
            
            /// @warning aka proposal: тогда вызов этих функций без предварительного вызова getRenderTarget UB.
    
        virtual bool onMouseMove      (MouseContext context)    = 0;
        virtual bool onMouseRelease   (MouseContext context)    = 0;
        virtual bool onMousePress     (MouseContext context)    = 0;
        virtual bool onKeyboardPress  (KeyboardContext context) = 0;
        virtual bool onKeyboardRelease(KeyboardContext context) = 0;
        virtual bool onClock(uint64_t delta) = 0;
    
    	virtual uint8_t getPriority() = 0;
    };
}

#endif // SYM_EVENT_PROCESSABLE_I