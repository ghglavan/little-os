#ifndef WRITE_H_INCLUDE
#define WRITE_H_INCLUDE

#define WR_LEVEL_INFO 3
#define WR_LEVEL_DEGUB 2
#define WR_LEVEL_WARNING 1
#define WR_LEVEL_ERROR 0

/** We cand include stdarg so we will use this basic struct to store
 *  the variable list
 */
typedef struct
{
    void **va_params;
    unsigned int va_len;
} wr_va_list;

/** wr_fprintf
 *  Formats the string given by fmt using the va_list arguments. Prints the log_lvl
 *  followed by the formated string to fd (framebufer or serial)
 * 
 *  @param fd The fd for the print (0 for framebuffer, != 0 for serial)
 *  @param lvl The lvl this string is printed for
 *  @param format The format string
 *  @param list The arguments for the format string
 */
int wr_fprintf(unsigned int fd, unsigned int lvl, char *format, wr_va_list list);

#endif // WRITE_H_INCLUDE