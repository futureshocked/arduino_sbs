#include "Wire.h"
void setup()
{
 Wire.begin(); 
 Wire.beginTransmission(0x20);
 Wire.write(0x00); 
 Wire.write(0x00);
 Wire.endTransmission();
}

void loop()
{
    delay(100);
    Wire.beginTransmission(0x20);
    Wire.write(0x12); 
    Wire.write(B10000000); 
    Wire.endTransmission();
    delay(100);
    Wire.beginTransmission(0x20);
    Wire.write(0x12); 
    Wire.write(B00000000);
    Wire.endTransmission();    
}
