#include <string.h>

#include "EditBox.h"


bool EditBox::OnMousePress(MouseCondition mouse)
{
    if (InsideP(mouse.position))
    {
        if (cursor_pos == -1)
        {
            text.Clear();
            cursor_pos = 0;
            return true;
        }

        int text_length = text.GetLength();
        for (int i = 0; i < text_length - 1; i++)
        {
            if (position.GetX() + i * letter_width <= mouse.position.GetX() &&
                position.GetX() + (i + 1) * letter_width > mouse.position.GetX())
            {
                cursor_pos = i;
                return true;
            }
        }

        cursor_pos = text_length;
        return true;
    }

    return false;
}

bool EditBox::OnKeyPress(Key key)
{
    if (cursor_pos != -1)
    {
        if (key <= Z)
        {
            text[cursor_pos] = 
        }

        cursor_pos++;
        return true;
    }

    return false;
}