//This sketch retrieves a value, like a secret pin
//from the EEPROM

#include <EEPROMex.h>

int addr = 0;

void setup()
{
  Serial.begin(9600);

  int retrievePin;

  retrievePin = EEPROM.readInt(addr);
  Serial.println(retrievePin);
  Serial.print("My pin is:");
  Serial.print(retrievePin);
  Serial.println(".");
}

void loop()
{
 
}
