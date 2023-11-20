#ifndef SYM_LABEL
#define SYM_LABEL

#include "../Widget.h"
#include "../../../Font/Font.h"

class Label : public Widget
{
    Font  font;
    int   character_size;
    char* text;
    plugin::Color text_color;
    plugin::Color background;

public:
    Label(plugin::Vec2 _position, Font font, int character_size, 
          const char* text = "Label", plugin::Color background = plugin::Color(0, 0, 0), 
          plugin::Color text_color = plugin::Color(255, 255, 255));
    ~Label();

    void SetText(const char* new_text);

    void Render(RenderTarget* render_target) override;
};

#endif //SYM_LABEL