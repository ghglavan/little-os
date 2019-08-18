#include "write.h"

void write_hello()
{
	int dec = 12, octal = 0123, hexa = 0xff;
	char c = 'c';
	void *v_args[] = {"Hello! I'm a string", &c, &dec, &octal, &hexa};
	wr_va_list l = {.va_params = v_args, .va_len = 5};
	wr_fprintf(0, WR_LEVEL_DEGUB, "Welcome to ObetaOS\nWe now know to printf :D.\nHere is a string: %s\nHere is a char: %c\nHere is a decimal: %d\nHere is an octal: %o\nHere is a hexadecimal: %x\n", l);
}