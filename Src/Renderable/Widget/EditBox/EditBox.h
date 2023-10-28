#ifndef SYM_EDIT_BOX
#define SYM_EDIT_BOX

#include "../Widget.h"

class EditBox : public Widget
{
    Font  font;
    DynArray<char> text;
    u_int cursor_pos;
    int   letter_width;

public: 
    EditBox(Vector position, Vector size, 
            Font _font, int _letter_width) :
    Widget      (position, size),
    font        (_font),
    letter_width(_letter_width),
    cursor_pos  (-1),
    text        (DynArray<char>(0))
    {
        text.PushBack('T');
        text.PushBack('e');
        text.PushBack('x');
        text.PushBack('t');
    }

    bool OnMousePress(MouseCondition mouse) override;
    bool OnKeyPress  (Key key) override;
};

#endif //SYM_EDIT_BOX