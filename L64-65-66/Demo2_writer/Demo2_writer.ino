//This sketch writes a value, like a secret pin
//to the EEPROMex

#include <EEPROMex.h>

int addr = 0;

void setup()
{
  Serial.begin(9600);
  int myPin=1234;
  EEPROM.writeInt(addr, myPin);

  Serial.print("My pin recorded:");
  Serial.print(myPin);
  Serial.println(".");
}

void loop()
{
 
}
