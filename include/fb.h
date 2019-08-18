#ifndef FB_H_INCLUDE
#define FB_H_INCLUDE

/** fb_putc:
 *  Writes the given char to the framebuffer with gey on green bg and advances the cursor acordingly
 * 
 *  @param c The char to be written
 */
void fb_putc(const char c);

#endif // FB_H_INCLUDE