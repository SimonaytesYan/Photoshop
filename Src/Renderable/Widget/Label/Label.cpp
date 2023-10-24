#include "Label.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

#include <string.h>

Label::Label(Vector _position, Font _font, int _character_size, 
             const char* _text, Color _background) :
Widget(_position, Vector(strlen(_text) * (_character_size - 5), (_character_size + 10))),
font           (_font),
character_size (_character_size),
background     (_background),
text           (_text)
{
}

Label::~Label()
{}

void Label::SetText(const char* new_text)
{
    text = new_text;
}

void Label::Render(RenderTarget* render_target)
{
    if (available)
    {
        render_target->DrawRect(position, size, reg_set, background);
        render_target->DrawText(position, font, text, character_size, reg_set);

        Widget::Render(render_target);
    }
}