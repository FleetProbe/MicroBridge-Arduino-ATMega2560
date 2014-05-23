USB and SDCARD Firmware flashing for the ARDUINO ATMEGA 2560 and ADK
---------------------------------------------------------------------

master branch is sdcard flash
bootloader_from_flash is flash from an spi chip


mechanics :

The bootloader looks for byte in eeprom at address 0x1FF:
	
	-if it is set to 0xF0 bootloader will look for a bin file on the sdcard named 
	 firmware.bin and use it to flash the firmware then reset the byte to 0xFF so it
	 does this only once
	
	-otherwise no action is taken and bootloader works as a arduino bootloader except
	 some of the debugging functions are missing
	 
Setup
	ADAFruit micro sdcard 5V ready:
	
	SDCARD on ATMEGA 2560 or ADK
	
	pin 50  -  DO
	
	pin 51  -  DI
	
	pin 52  -  CLK
	
	pin 53  -  CS
	
	if you have an sd card shield which is different from this setup you need to change 
	the pinout in asmfunc.S and recompile the bootloader !!!
	
Flashing bootloader :
	
	- copy the entire 'hardware' folder to your mydocuments/arduino folder 
	
	- restart arduino ide
	
	- you should now see under tools -> boards  -> Arduino mega 2560 (Dual sd bootloader) (select this)
	
	- set the appropriate programmer
	
	- burn bootloader
	
Using arduino ISP bootloader :
	
	- connect arduino atmega 2560
	
	- upload sketch 'Arduino ISP' (found in file -> examples)

	Atmega2560 to Atmega 2560 connections:
		programmer	-	receiver
		pin 50			pin 50
		pin 51			pin 51
		pin 52			pin 52
		pin 53			reset
		5v				5v
		ground			ground
	aditionally on programmer you have to put a capacitor between reset and ground (2.2microf works)
	if you don't do this it won't work !!!

Compile bootloader:

install Crosspack (http://www.obdev.at/products/crosspack/index.html)

Navigate to My Documents/arduino/hardware/microbridge/bootladers/microbridge/

issue : 
	
	- make clean
	
	- make all

	bootloader output :
	
	Size after:
	AVR Memory Usage
	----------------
	Device: atmega2560

	Program:    6116 bytes (2.3% Full)
	(.text + .data + .bootloader)

	Data:        333 bytes (4.1% Full)
	(.data + .bss + .noinit)


Generate BIN file:

To generate a bin file you need issue the following command on you apps elf executable :

	avr-objcopy -I elf32-avr -O binary firmware.cpp.elf firmware.bin

this generates firmware.bin which can be put on the sd for flashing your firmware. You can find the elf 
file in you apps build directory.

Using olimex usb to upload bootloader:
	avrdude -c stk500v2 -p m2560 -P /dev/tty.usbmodemfd131 -B 500 -e -u -U lock:w:0x3F:m -U efuse:w:0xFD:m -U hfuse:w:0xD8:m -U efuse:w:0xFF:m -F

	avrdude -p m2560 -c stk500v2 -P /dev/tty.usbmodemfa131 -F -U flash:w:stk500boot.hex -b 115200 -B1 -U lock:w:0x0F:m
	
	avrdude -p m168 -c usbtiny -e -u -U lock:w:0x3f:m -U efuse:w:0x00:m -U hfuse:w:0xDD:m -U lfuse:w:0xFF:m
	
	
	avrdude -p m2560 -c stk500v2 -P /dev/tty.usbmodemfd131 -U flash:w:stk500boot_v2_mega2560.hex -U lock:w:0x0F:m -v 
	avrdude -c stk500v2 -p m2560 -P /dev/tty.usbmodemfd131 -U lock:w:0x3F:m -U efuse:w:0xFD:m -U hfuse:w:0xD8:m -U lfuse:w:0xFF:m -e -v
