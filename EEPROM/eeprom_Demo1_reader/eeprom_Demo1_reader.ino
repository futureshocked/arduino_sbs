//This sketch retrieves a value, like a secret pin
//from the EEPROM

#include <EEPROM.h>

int addr = 0;

void setup()
{
  Serial.begin(9600);

  byte retrievePinHigh;
  byte retrievePinLow;
  retrievePinHigh = EEPROM.read(addr);
  retrievePinLow = EEPROM.read(addr+1);
  Serial.println(retrievePinHigh);
  Serial.println(retrievePinLow);
  Serial.print("My pin is:");
  Serial.print((retrievePinHigh << 8) + retrievePinLow);
  Serial.println(".");
}

void loop()
{
 
}
