//This sketch writes a value, like a secret pin
//to the EEPROM

#include <EEPROM.h>

int addr = 0;

void setup()
{
  Serial.begin(9600);
  int myPin=1234;
  EEPROM.write(addr, highByte(myPin));
  EEPROM.write(addr+1, lowByte(myPin));

  Serial.print("My pin recorded:");
  Serial.print(myPin);
  Serial.println(".");
}

void loop()
{
 
}
