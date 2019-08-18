# Obeta OS
Minimal (as minimal as it can be) os based on [little os book](https://littleosbook.github.io). So far we can only write to the screen, move the cursor using the framebuffer and write to serial port COM1(0x3F8). We dont have a bootloader so we use grub .You can find the binary [here](http://littleosbook.github.com/files/stage2_eltorito). The reason we dont build it by hand is that we heard that the `configure` script doesn't work well on ubuntu systems and I'm to lazy to check.

We use NASM as the assembler and `bochs` for virtualization.

Requirements:
```
sudo apt-get install build-essential nasm genisoimage bochs bochs-sdl
``` 
The tree should look like this:
```
iso
    |-- boot
      |-- grub
      | |-- menu.lst
      | |-- stage2_eltorito
      |-- kernel.elf
```
I didn't add `stage2_eltorito` so you should download and copy it to the right place or you can use the `setup.sh` script.`kernel.elf` will be moved inside os directory by `make run`.

So far all we can do is print in a prinf-like style (even tho we dont have va_list) using the framebuffer and move the cursor or using the serial. I know is not much but is a start.

## Building

To build and run:
```
make run
```
then, in console type `c` to continue the simulation and start the boot process.
When you get bored of looking at the screen, you can use `C^ c` to pause `bochs` and `q` to quit. 
