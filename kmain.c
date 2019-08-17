/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
static int t;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{ 
    (void)t;
    char* fb = (char*) 0x000B8000;
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void print_str(char* s) {
	int idx = 0;
	for (int i = 0; s[i] != 0; ++i) {
		fb_write_cell(idx++, s[i], 2, 8);
		idx++;	
	}	       
}

