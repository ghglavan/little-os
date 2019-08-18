#include "serial.h"

void write_hello()
{
	serial_write("Hello from Obeta OS\n\tHope you like it!", 1000);
}