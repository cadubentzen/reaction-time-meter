Reaction Time Meter
========================

A Bleaglebone Black project using GPIO and LCD 20x4 display to measure the reaction time for a user to press a button.

## Getting Started

**To avoid possible permission troubles, run the following steps as root.**

To compile with printing to the console, simply run `make`. 

If you want to display the result on a LCD display, first follow the steps in README of <https://github.com/gorskima/hd44780-i2c> to compile and add kernel module of LCD I2C display. Then compile running `make CFLAGS=-DLCD_DISPLAY`. If switching between using LCD or not, make sure to clean the project first: `make clean`.

Currently, this needs to be compiled on board. But it could be easily cross-compiled changing CC in src/Makefile.

To run: `./reaction`.

## Third-party code

The access to GPIO in user space is based on the Sysfs interface (<https://www.kernel.org/doc/Documentation/gpio/sysfs.txt>) and the C code to access the files via system call is reused from <https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c>.

In addition, a LCD 20x4 display is used. For this purpose, this device driver is used: <https://github.com/gorskima/hd44780-i2c>.

## Authors
- Cadu Bentzen - **cadubentzen at gmail.com**
- Igor Macedo - **igormacedo94 at gmail.com**
