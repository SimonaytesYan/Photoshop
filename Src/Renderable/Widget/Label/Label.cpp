#include "Label.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

#include <string.h>

Label::Label(plugin::Vec2 _position, Font _font, int _character_size, 
             const char* _text, plugin::Color _background, plugin::Color _text_color) :
Widget(_position, plugin::Vec2(strlen(_text) * (_character_size - 5), (_character_size + 10))),
font           (_font),
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

void Label::render(RenderTarget* render_target)
{
    if (available)
    {
        render_target->DrawRect(position, size, reg_set, background);
        render_target->DrawText(position, font, text, character_size, text_color, reg_set);

        Widget::render(render_target);
    }
}
