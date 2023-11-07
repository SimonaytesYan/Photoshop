#include <string.h>

#include "EditBox.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

Vector kIndent = Vector(10, 0);

bool EditBox::OnMousePress(MouseCondition mouse)
{
    bool widget_return = Widget::OnMousePress(mouse);
    if (widget_return)
        return widget_return;
    
    if (InsideP(mouse.position))
    {
        fprintf(stderr, "InsideP EditBox\n");
        if (cursor_pos == EDIT_BOX_UNUSED || cursor_pos == EDIT_BOX_UNABLE)
        {
            text.Clear();
            cursor_pos = 0;
            fprintf(stderr, "cursor pos = %d\n", cursor_pos);
            return true;
        }

        int mouse_x = mouse.position.GetX() - position.GetX();

        int text_length = text.GetLength();
        for (int i = 0; i < text_length - 1; i++)
        {
            if (i       * letter_width * chapter_size <= mouse_x &&
                (i + 1) * letter_width * chapter_size >  mouse_x)
            {
                cursor_pos = i;
                fprintf(stderr, "cursor pos = %d\n", cursor_pos);
                return true;
            }
        }

        cursor_pos = text_length;
        fprintf(stderr, "cursor pos = %d\n", cursor_pos);
        return true;
    }
    
    cursor_pos = EDIT_BOX_UNABLE;
    return false;
}

bool EditBox::OnKeyPress(Key key)
{
    if (cursor_pos != EDIT_BOX_UNABLE && cursor_pos != EDIT_BOX_UNUSED)
    {
        if (key == Backspace || key == Left || key == Right) // keys, control 
        {
            if (key == Left)
            {
                if (cursor_pos > 0)
                    cursor_pos--;
            }
            else if (key == Right)
            {
                if (cursor_pos < text.GetLength())
                    cursor_pos++;
            }
            else if (key == Backspace)
            {
                if (cursor_pos > 0)
                {
                    text.Remove(cursor_pos - 1);
                    cursor_pos--;
                }
            }
        }
        else
        {
            if (key <= Z)
                text.Insert(key + 'a', cursor_pos);
            else if (key <= Num9)
                text.Insert(key - Num0 + '0', cursor_pos);
            else if (key == Comma)
                text.Insert(',', cursor_pos);
            else if (key == Period)
                text.Insert('.', cursor_pos);
            else 
                return true;

            cursor_pos++;
        }
        return true;
    }

    return false;
}

bool EditBox::OnClock(size_t delta)
{
    cursor_visible = !cursor_visible;
    return false;
}

void EditBox::Render(RenderTarget* rt)
{
    if (available)
    {
        // Frame
        rt->DrawRect(position, size, reg_set, Color(255, 255, 255), 3);
        
        if (text.GetCapacity() > text.GetLength() + 1)
            text[text.GetLength()] = 0;
        else
            text.PushBack(0);

        // Text inside
        rt->DrawText(position + kIndent, font, 
                     text.GetArray(), chapter_size, Color(0, 0, 0), reg_set);

        // Cursor
        if (cursor_pos != EDIT_BOX_UNABLE && cursor_pos != EDIT_BOX_UNUSED && 
            cursor_visible)
        {
            rt->DrawRect(position + Vector(letter_width * chapter_size * cursor_pos, 0) + kIndent, 
                         Vector(4, chapter_size * letter_height), reg_set, Color(0, 0, 0));
        }
    }
}