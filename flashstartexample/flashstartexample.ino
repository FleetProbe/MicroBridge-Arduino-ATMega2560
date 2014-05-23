/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
#include "EEPROM.h"
#include <avr/wdt.h>
// the setup routine runs once when you press reset:
void setup() {                
  Serial.begin(115200);
  Serial.println("Press 'F' and 'enter' to set flagbit in eeprom 0x1FF to 0xF0 ");
  Serial.println("also to induce watchdog timeout which triggers the bootloader ");
  Serial.println("and flashes the new firmware on the sd card");

}

// the loop routine runs over and over again forever:
void loop() {
 char inChar = '\0';

 while (Serial.available() > 0) {
   inChar = Serial.read();
 }
   wdt_enable(WDTO_500MS); // have the wdt reset the chip
  // if 500ms passes without a reset
 if(inChar == 'F'){
    Serial.println("");
    Serial.println("rebooting and flashing with firmware.bin on sdcard"); 
    EEPROM.write(0x1FF,0xF0);
    wdt_reset();
    delay(600); // wait 600ms to timeout wdt
 }
}
