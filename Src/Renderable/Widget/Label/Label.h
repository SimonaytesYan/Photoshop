#ifndef SYM_LABEL
#define SYM_LABEL

#include "../Widget.h"
#include "../../../Font/Font.h"

class Label : public Widget
{
    Font        font;
    int         character_size;
    const char* text;
    Color       background;

public:
    Label(Vector _position, Font font, int character_size, 
          const char* text = "Label", Color background = Color(0, 0, 0));
    ~Label();

    void SetText(const char* new_text);

    void Render(RenderTarget* render_target) override;
};

#endif //SYM_LABEL