#ifndef SERIAL_H_INCLUDE
#define SERIAL_H_INCLUDE

/** serial_write:
 *  Writes the given string to the SERIAL_COM1_BASE port
 * 
 *  @param buf The string to be written
 *  @param len The length of the string
 */
int serial_write(char *buf, unsigned int len);

#endif // SERIAL_H_INCLUDE