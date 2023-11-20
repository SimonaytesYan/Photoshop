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
    bool   cursor_visible;

public: 
    EditBox(plugin::Vec2 position, plugin::Vec2 size, 
            Font _font, double _letter_width, double _letter_height, int _chapter_size) :
    Widget         (position, size),
    font           (_font),
    letter_width   (_letter_width),
    letter_height  (_letter_height),
    chapter_size   (_chapter_size),
    cursor_pos     (EDIT_BOX_UNUSED),
    cursor_visible (false),
    text           (DynArray<char>(0))
    {
        text.PushBack('T');
        text.PushBack('e');
        text.PushBack('x');
        text.PushBack('t');
    }

    const char* GetText()
    {
        if (text.GetCapacity() > text.GetLength() + 1)
            text[text.GetLength()] = 0;
        else
            text.PushBack(0);
        return text.GetArray();
    }

    bool onMousePress(MouseContext mouse) override;
    bool onKeyboardPress  (KeyboardContext key)              override;
    bool onClock     (size_t delta)         override;
    void render      (RenderTarget* rt)     override;
};

#endif //SYM_EDIT_BOX