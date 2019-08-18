#include "fb.h"
#include "serial.h"
#include "write.h"

#define WR_LOG_MAX_LEVEL 3 // max log level allowed

typedef void (*wr_putc_f)(const char);

static void puts(const char *s, wr_putc_f putc)
{
    for (unsigned int i = 0; s[i] != 0; ++i)
    {
        putc(s[i]);
    }
}

static const char *wr_log_level_to_string(unsigned int log_level)
{
    if (log_level == WR_LEVEL_ERROR)
        return "[ERR]";
    if (log_level == WR_LEVEL_WARNING)
        return "[WRN]";
    if (log_level == WR_LEVEL_DEGUB)
        return "[DBG]";
    if (log_level == WR_LEVEL_INFO)
        return "[INF]";

    return "[UNK]";
}

static char *convert(unsigned int num, int base)
{
    static char representation[] = "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = representation[num % base];
        num /= base;
    } while (num != 0);

    return ptr;
}

int wr_fprintf(unsigned int fd, unsigned int lvl, char *format, wr_va_list list)
{
    if (lvl > WR_LOG_MAX_LEVEL)
        return -2;

    char *traverse;

    unsigned int ui;
    int i;
    const char *s;
    char c;

    unsigned int va_len = list.va_len, va_index = 0;

    const char *lvl_string = wr_log_level_to_string(lvl);
    wr_putc_f putc = 0;

    if (fd == 0)
    {
        putc = fb_putc;
    }
    else
    {
        putc = serial_putc;
    }

    puts(lvl_string, putc);
    putc(':');

    for (traverse = format; *traverse != 0; traverse++)
    {
        while (*traverse != '%' && *traverse != 0)
        {
            putc(*traverse);
            traverse++;
        }

        if (*traverse == 0)
            break;

        traverse++;
        if (va_index >= va_len)
            return -1;

        switch (*traverse)
        {
        case 'c':

            c = *(char *)list.va_params[va_index++]; //Fetch char argument
            putc(c);
            break;

        case 'd':
            i = *(int *)list.va_params[va_index++]; //Fetch Decimal/Integer argument
            if (i < 0)
            {
                i = -i;
                putc('-');
            }
            puts(convert(i, 10), putc);
            break;

        case 'o':
            ui = *(unsigned int *)list.va_params[va_index++]; //Fetch Octal representation
            puts(convert(ui, 8), putc);
            break;

        case 's':
            s = (const char *)list.va_params[va_index++]; //Fetch string
            puts(s, putc);
            break;

        case 'x':
            ui = *(unsigned int *)list.va_params[va_index++]; //Fetch Hexadecimal representation
            puts(convert(ui, 16), putc);
            break;
        }
    }

    return traverse - format;
}
