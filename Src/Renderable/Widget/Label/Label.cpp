#include "Label.h"

Label::Label(Vector _position, Font _font, int _character_size, const char* _text) :
Widget(_position),
font (_font),
character_size (_character_size),
text (_text)
{}

Label::~Label()
{}

void Label::SetText(const char* new_text)
{
    text = new_text;
}

void Label::Render(RenderTarget* render_target)
{
    render_target->DrawText(position, font, text, character_size);

    Widget::Render(render_target);
}