#ifndef IO_H_INCLUDE
#define IO_H_INCLUDE

/** outb:
 *  Sends the given data to the given I/O port
 *  Defined in io.s
 * 
 * @param port The I/O port ti send data to
 * @param data The data to send
 */
void outb(unsigned short port, unsigned int data);

/** inb:
 *  Read a byte from an I/O port
 * 
 *  @param port The port to read from
 *  @return     The read byte 
 */
unsigned char inb(unsigned short port);

#endif // IO_H_INCLUDE