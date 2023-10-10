#include "Label.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

#include <string.h>

Label::Label(Vector _position, Font _font, int _character_size, const char* _text) :
Widget(_position),
font (_font),
character_size (_character_size),
text (_text)
{
    Vector size(character_size, strlen(_text) * character_size);
    reg_set.AddRegion(ClipRegion(_position, size));
}

Label::~Label()
{}

void Label::SetText(const char* new_text)
{
    text = new_text;
}

void Label::Render(RenderTarget* render_target)
{
    render_target->DrawText(position, font, text, character_size, reg_set);

    Widget::Render(render_target);
}