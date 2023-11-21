#ifndef SYM_GUI
#define SYM_GUI

#include "../Standart/GuiI.h"
#include "../Renderable/Widget/Widget.h"

class Gui : public plugin::GuiI
{
    Widget* root;

public:
    plugin::Vec2 getSize() override
    { return root->getSize(); }
    /// @brief запросить RT.
    /// Хост создает новое окно / отдает какое-то, абсолютно пустое, с единственным RT на все окно.
    /// @param size -- размер запрашиваемой области
    /// @param pos  -- (относительное [относительно предоставленной области]) смещение запрашиваемой области
    plugin::RenderTargetI* getRenderTarget(plugin::Vec2 size, 
                                           plugin::Vec2 pos, 
                                           plugin::Plugin *self) override;

    /// @brief Создает окно с параметрами, каким-то образом узнает у пользователя 
    ///     значения параметров и потом возвращает их интерфейсу через Interface::set_params
    /// @note окно не обязательно модальное, да и вообще implementation defined. Мем в том, что плагин находится в 
    ///     неопределенном/дефолтном состоянии между createParamWindow и Interface::set_params и взаимодействие с ним UB
    void createParamWindow(plugin::Array<const char*> param_names, 
                           plugin::Interface*         self) override;

    /**
     * @brief Get the root widget of widget tree
     * 
     * @return WidgetI* root
     */
    plugin::WidgetI* getRoot() override
    { return root; }
};

#endif //SYM_GUI
