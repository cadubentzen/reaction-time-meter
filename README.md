Reaction Time Meter
========================

A Bleaglebone Black project using GPIO and LCD 20x4 display to measure the reaction time for a user to press a button.

## Getting Started ##
### Connecting to the Bleaglebone Black ###
On a Linux system
1. Connect your BeagleBone to your computer by using a Mini USB cable.
2. Open the terminal and type `ifconfig`. You should see a network adapter that has one of the following ips `192.168.7.1` or `192.168.6.1`
3. Then the BeagleBone itself will have the ip `192.168.6.2` or `192.168.7.2`
4. Then connect via ssh with the command `ssh debian@192.168.7.2`, use sudo and/or change the ip if necessary. Make sure you're connecting with the correct username in ssh

#### Share internet connection over the USB ####
Reference: <https://elementztechblog.wordpress.com/2014/12/22/sharing-internet-using-network-over-usb-in-beaglebone-black/>

On the BeagleBone Board, run (attempt to the correct ip address, it could be either `192.168.6.#` or `192.168.7.#`)
```
ifconfig usb0 192.168.6.2
route add default gw 192.168.6.1
```

On the PC host, run (ATTENTION: change the `wlan0` to yout internet interface and `eth0` to the network adapter of the BeagleBone. And mind the ip address as well)
```
sudo su
ifconfig eth5 192.168.6.1
iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE
iptables --append FORWARD --in-interface eth0 -j ACCEPT
echo 1 > /proc/sys/net/ipv4/ip_forward
```
### Running the project ###

**To avoid possible permission troubles, run the following steps as root. Use `sudo su`**

To compile with printing to the console, go to the project folder and simply run `make`.

If you want to display the result on a LCD display, first follow the steps in README of <https://github.com/gorskima/hd44780-i2c> to compile and add kernel module of LCD I2C display (see the usage below, copied and modified from gorskima).
#### Usage ####
1. In the reaction-time-meter folder, run `insmod ../hd44780-i2c/hd44780.ko` to add the kernel module
2. Let the I2C adapter know that there's a new device attached: `echo hd44780 0x27 > /sys/class/i2c-adapter/i2c-1/new_device`. You may need to replace the device's I2C address and adapter path with proper values. For example, consider changing the `i2c-1` to `i2c-2`, if you get `bash: /sys/class/i2c-adapter/i2c-1/new_device: No such file or directory`
3. At this point a new device should appear (`/dev/lcd0`) and you should be able to write to it
4. For more information, see the github repository of the hd44780 driver.

Then compile running `make CFLAGS=-DLCD_DISPLAY`. If switching between using LCD or not, make sure to clean the project first: `make clean`.

Currently, this needs to be compiled on board. But it could be easily cross-compiled changing CC in src/Makefile.

To run: `./reaction`.

## Third-party code ##

The access to GPIO in user space is based on the Sysfs interface (<https://www.kernel.org/doc/Documentation/gpio/sysfs.txt>) and the C code to access the files via system call is reused from <https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c>.

In addition, a LCD 20x4 display is used. For this purpose, this device driver is used: <https://github.com/gorskima/hd44780-i2c>.

## Authors ##
- Cadu Bentzen - **cadubentzen at gmail.com**
- Igor Macedo - **igormacedo94 at gmail.com**
