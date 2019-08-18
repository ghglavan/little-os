#include "io.h"

#define SERIAL_COM1_BASE 0x3F8
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

// Tells the serial port to expect the highest 8 bits on data port and
// then expect the lowest 8 bits
#define SERIAL_LINE_ENABLE_DLAB 0x80

/** serial_configure_baud_rate
 *  Sets the speed of the data being send. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s
 * 
 *  @param com The com port to configure
 *  @param divisor The divisor
 */
static void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
static void serial_configure_line(unsigned short com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/** serial_configure_buffer:
 *  Configures the buffer of the given serial port. The port is set to:
 *  * Enable FIFO
 *  * Clear both receiver and transmission FIFO queues
 *  * Use 14 bytes as size of queue
 *
 *  @param com  The serial port to configure
 */
static void serial_configure_buffer(unsigned short com)
{
    /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
     * Content: | lvl | bs | r | dma | clt | clr | e |
     * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/** serial_configure_modem:
 *  Configures the modem of the given serial port. The port is set to enable
 *  RTS and DTS
 * 
 *  @param com  The serial port to configure
 */
static void serial_configure_modem(unsigned short com)
{
    /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
     * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
     * Value:   | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1   | = 0x03
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/** serial_is_transmit_fifo_empty
 *  Checks if the transmit FIFO is empty for a given com port
 * 
 * @param com The COM port
 * @return 0  The queue is not empty
 *         1  The queue is empty
 */
static int serial_is_transmit_fifo_empty(unsigned int com)
{
    // 0x20 = 0010 0000
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

static int serial_setup_done = 0;

int serial_write(const char *buf, unsigned int len)
{

    if (!serial_setup_done)
    {
        serial_configure_baud_rate(SERIAL_COM1_BASE, 1);
        serial_configure_line(SERIAL_COM1_BASE);
        serial_configure_buffer(SERIAL_COM1_BASE);
        serial_configure_modem(SERIAL_COM1_BASE);
        serial_setup_done = 1;
    }

    unsigned int i = 0;
    for (; i < len && buf[i] != 0; ++i)
    {
        while (!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE))
        {
        }
        outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buf[i]);
    }

    return i;
}