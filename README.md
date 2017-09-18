Reaction Time Meter
========================

A Bleaglebone Black project using GPIO to measure the reaction time for a user to press a button.

## Getting Started

To compile with printing on the console, simply run `make`. If you want to display the result on a LCD display, first configure it following README in <https://github.com/gorskima/hd44780-i2c> and compile running `make CFLAGS=-DLCD_DISPLAY`. If switching between using LCD or not, make sure to clean the project first: `make clean`.

Currently, this needs to be compiled on board. But it could be easily cross-compiled changing CC in src/Makefile.

To run: `./reaction`.

## Third-party code

The access to GPIO in user space is based on the Sysfs interface (<https://www.kernel.org/doc/Documentation/gpio/sysfs.txt>) and the C code to access the files via system call is reused from <https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c>.

In addition, a LCD 20x4 display will be used. For this purpose, this device driver is used: <https://github.com/gorskima/hd44780-i2c>.

## Authors
- Cadu Bentzen - **cadubentzen at gmail.com**
- Igor Macedo - **igormacedo94 at gmail.com**
