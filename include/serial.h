#ifndef SERIAL_H_INCLUDE
#define SERIAL_H_INCLUDE

/** serial_putc:
 *  Writes the given char to the SERIAL_COM1_BASE port
 * 
 *  @param c The char to be written
 */
void serial_putc(const char c);

#endif // SERIAL_H_INCLUDE