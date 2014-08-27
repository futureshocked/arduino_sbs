#include "Wire.h"
void setup()
{
 Wire.begin(); 
 Wire.beginTransmission(0x20);
 Wire.write(0x00); // IODIRA register
 Wire.write(0x00); // Set all ports to outputs
 Wire.endTransmission();
 
 Wire.beginTransmission(0x20);
 Wire.write(0x01); // IODIRB register
 Wire.write(0x00); // Set all ports to outputs
 Wire.endTransmission();
}

void loop()
{
    delay(100);
    Wire.beginTransmission(0x20);
    Wire.write(0x12); //Select Bank A
    Wire.write(B10000000); 
    Wire.endTransmission();
    Wire.beginTransmission(0x20);
    Wire.write(0x13); //Select Bank B
    Wire.write(B00000001); 
    Wire.endTransmission();
    
    delay(100);
    Wire.beginTransmission(0x20);
    Wire.write(0x12); 
    Wire.write(B00000000);
    Wire.endTransmission();    
    Wire.beginTransmission(0x20);
    Wire.write(0x13); 
    Wire.write(B00000000);
    Wire.endTransmission();  
}
