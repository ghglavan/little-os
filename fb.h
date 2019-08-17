#ifndef FB_H_INCLUDE
#define FB_H_INCLUDE

/** fb_write:
 *  Writes the given string to the framebuffer with gey on green bg and advances the cursor acordingly
 * 
 *  @param buf The string to be written
 *  @param len The length of the string
 */
int fb_write(char *buf, unsigned int len);

#endif // FB_H_INCLUDE