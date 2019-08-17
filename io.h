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

#endif // IO_H_INCLUDE