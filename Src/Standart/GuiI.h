#ifndef SYM_GUI_I
#define SYM_GUI_I

#include "../Standart/Standart.h"
#include "RenderTargetI.h"
#include "WidgetI.h"
#include "../Useful.h"
#include "Plugin.h"
#include "Interface.h" 

namespace plugin
{
    struct GuiI 
    {
        virtual Vec2 getSize() = 0; // размер доступной для рисования площади (которую можно запросить)

        /// @brief запросить RT.
        /// Хост создает новое окно / отдает какое-то, абсолютно пустое, с единственным RT на все окно.
        /// @param size -- размер запрашиваемой области
        /// @param pos  -- (относительное [относительно предоставленной области]) смещение запрашиваемой области
        virtual RenderTargetI* getRenderTarget(Vec2 size, Vec2 pos, Plugin *self) = 0;

        /// @brief Создает окно с параметрами, каким-то образом узнает у пользователя 
        ///     значения параметров и потом возвращает их интерфейсу через Interface::set_params
        /// @note окно не обязательно модальное, да и вообще implementation defined. Мем в том, что плагин находится в 
        ///     неопределенном/дефолтном состоянии между createParamWindow и Interface::set_params и взаимодействие с ним UB
        virtual void createParamWindow(Array<const char *> param_names, Interface * self) = 0;

        /**
         * @brief Get the root widget of widget tree
         * 
         * @return WidgetI* root
         */
        virtual WidgetI* getRoot() = 0;
    };
} 

#endif //SYM_GUI_I