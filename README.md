Reaction Time Meter
========================

A Bleaglebone Black project using GPIO to measure the reaction time for a user to press a button.

## Getting Started

TODO

## Third-party code

The access to GPIO in user space is based on the Sysfs interface (<https://www.kernel.org/doc/Documentation/gpio/sysfs.txt>) and the C code to access the files via system call is reused from <https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c>.

In addition, a LCD 20x4 display will be used. For this purpose, this device driver is going to be used: <https://github.com/lucidm/lcdi2c>.

## Authors
- Cadu Bentzen - **cadubentzen at gmail.com**
- Igor Macedo - **igormacedo94 at gmail.com**
