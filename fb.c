#include "io.h"

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

#define FB_COLOR_DARK_GREY 8
#define FB_COLOR_GREEN 2

short fb_cursor_x = 0;
short fb_cursor_y = 0;
const unsigned short fb_line_w = 80;
const unsigned short fb_line_h = 25;

/** fb_move_cursor
 * 	Moves the cursor of the framebuffer to the given position
 * 
 * @param pos The position to move the cursor to
 */
static void fb_move_cursor()
{
    unsigned int pos = fb_cursor_y * fb_line_w + fb_cursor_x;
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer and moves the cursor.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
static void fb_write_cell(char c, unsigned char fg, unsigned char bg)
{
    unsigned int i = fb_cursor_y * fb_line_w + fb_cursor_x;
    i *= 2;

    unsigned char dont_print = 0;

    if (c == '\n')
    {
        fb_cursor_y += 1;
        fb_cursor_x = 0;
        dont_print = 1;
    }
    else if (c == '\t')
    {
        fb_cursor_x += 4;
        dont_print = 1;
    }
    else
        fb_cursor_x += 1;

    if (fb_cursor_x >= fb_line_w)
    {
        fb_cursor_x %= fb_line_w;
        fb_cursor_y += 1;
    }

    if (fb_cursor_y >= fb_line_h)
        fb_cursor_y %= fb_line_h;

    fb_move_cursor();

    if (!dont_print)
    {
        char *fb = (char *)0x000B8000;
        fb[i] = c;
        fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
    }
}

int fb_write(char *buf, unsigned int len)
{
    unsigned int cells_left = fb_line_w * fb_line_h - fb_cursor_y * fb_line_w + fb_cursor_x;
    if (len > cells_left)
        len = cells_left;

    unsigned int i;
    for (i = 0; i < len && buf[i] != 0; ++i)
    {
        fb_write_cell(buf[i], FB_COLOR_DARK_GREY, FB_COLOR_GREEN);
    }

    if (i < len)
        len = i;

    return len;
}
