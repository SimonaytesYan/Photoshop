#ifndef SYM_EDIT_BOX
#define SYM_EDIT_BOX

#include "../Widget.h"

enum CursorCond
{
    EDIT_BOX_UNUSED = -2,
    EDIT_BOX_UNABLE = -1,
};

class EditBox : public Widget
{
    Font  font;
    DynArray<char> text;
    int    cursor_pos;
    int    chapter_size;
    double letter_width;
    double letter_height;
    int    cursor_visible;

public: 
    EditBox(Vector position, Vector size, 
            Font _font, double _letter_width, double _letter_height, int _chapter_size) :
    Widget         (position, size),
    font           (_font),
    letter_width   (_letter_width),
    letter_height  (_letter_height),
    chapter_size   (_chapter_size),
    cursor_pos     (EDIT_BOX_UNUSED),
    cursor_visible (0),
    text           (DynArray<char>(0))
    {
        text.PushBack('T');
        text.PushBack('e');
        text.PushBack('x');
        text.PushBack('t');
    }

    bool OnMousePress(MouseCondition mouse) override;
    bool OnKeyPress  (Key key)              override;
    //TODO Implement Render 
    void Render      (RenderTarget* rt)     override;
};

#endif //SYM_EDIT_BOX