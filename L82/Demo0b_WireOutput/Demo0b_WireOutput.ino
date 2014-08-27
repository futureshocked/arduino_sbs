/*
 Example 41.1 - Microchip MCP23017 with Arduino
 http://tronixstuff.com/tutorials > chapter 41
 John Boxall | CC by-sa-nc
*/
// pins 15~17 to GND, I2C bus address is 0x20
#include "Wire.h"
void setup()
{
 Wire.begin(); // wake up I2C bus
// set I/O pins to outputs
 Wire.beginTransmission(0x20);
 Wire.write(0x00); // IODIRA register
 Wire.write(0x00); // set all of port A to outputs
 Wire.endTransmission();
 
 Wire.beginTransmission(0x20);
 Wire.write(0x01); // IODIRB register
 Wire.write(0x00); // set all of port B to outputs
 Wire.endTransmission();
}

void loop()
{
    delay(100);
    Wire.beginTransmission(0x20);
    Wire.write(0x12); // GPIOA
    Wire.write(B10000000); // port A
    Wire.endTransmission();
    
    Wire.beginTransmission(0x20);
    Wire.write(0x13); // GPIOB
    Wire.write(B00000000); // port B
    Wire.endTransmission();
 
    delay(100);
    Wire.beginTransmission(0x20);
    Wire.write(0x12); // GPIOA
    Wire.write(B00000000); // port A
    Wire.endTransmission();  
    Wire.beginTransmission(0x20);
    Wire.write(0x13); // GPIOB
    Wire.write(B0000010); // port B
    Wire.endTransmission();  

}

