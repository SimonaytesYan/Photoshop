#include <string.h>

#include "EditBox.h"
#include "../../../RegionSet/RegionSet.h"
#include "../../../ClipRegion/ClipRegion.h"

plugin::Vec2 kIndent = plugin::Vec2(10, 0);

bool EditBox::onMousePress(plugin::MouseContext mouse)
{
    bool widget_return = Widget::onMousePress(mouse);
    if (widget_return)
        return widget_return;
    
    if (InsideP(mouse.position))
    {
        if (cursor_pos == EDIT_BOX_UNUSED || cursor_pos == EDIT_BOX_UNABLE)
        {
            text.Clear();
            cursor_pos = 0;
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
                return true;
            }
        }

        cursor_pos = text_length;
        return true;
    }
    
    cursor_pos = EDIT_BOX_UNABLE;
    return false;
}

bool EditBox::onKeyboardPress(plugin::KeyboardContext keyboard)
{
    plugin::Key key = keyboard.key;

    if (cursor_pos != EDIT_BOX_UNABLE && cursor_pos != EDIT_BOX_UNUSED)
    {
        if (key == plugin::Key::Backspace || key == plugin::Key::Left || key == plugin::Key::Right) // keys, control 
        {
            if (key == plugin::Key::Left)
            {
                if (cursor_pos > 0)
                    cursor_pos--;
            }
            else if (key == plugin::Key::Right)
            {
                if (cursor_pos < text.GetLength())
                    cursor_pos++;
            }
            else if (key == plugin::Key::Backspace)
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
            int int_key = (int)key;
            if (key <= plugin::Key::Z)
                text.Insert((int)key + 'a', cursor_pos);
            else if (key <= plugin::Key::Num9)
                text.Insert((int)key - (int)plugin::Key::Num0 + '0', cursor_pos);
            else if (key == plugin::Key::Comma)
                text.Insert(',', cursor_pos);
            else if (key == plugin::Key::Period)
                text.Insert('.', cursor_pos);
            else 
                return true;

            cursor_pos++;
        }
        return true;
    }

    return false;
}

bool EditBox::onClock(size_t delta)
{
    cursor_visible = !cursor_visible;
    return false;
}

void EditBox::render(RenderTarget* rt)
{
    if (available && visible)
    {
        // Frame
        rt->DrawRect(position, size, reg_set, plugin::Color(255, 255, 255), 3);
        
        if (text.GetCapacity() > text.GetLength() + 1)
            text[text.GetLength()] = 0;
        else
            text.PushBack(0);

        // Text inside
        rt->DrawText(position + kIndent, font, 
                     text.GetArray(), chapter_size, plugin::Color(0, 0, 0), reg_set);

        // Cursor
        if (cursor_pos != EDIT_BOX_UNABLE && cursor_pos != EDIT_BOX_UNUSED && 
            cursor_visible)
        {
            rt->DrawRect(position + plugin::Vec2(letter_width * chapter_size * cursor_pos, 0) + kIndent, 
                         plugin::Vec2(4, chapter_size * letter_height), reg_set, plugin::Color(0, 0, 0));
        }
    }
}