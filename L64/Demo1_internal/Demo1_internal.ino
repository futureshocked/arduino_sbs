#include <EEPROM.h>

int addr = 0;

void setup()
{
  Serial.begin(9600);
  byte myPin=111;
  EEPROM.write(addr, myPin);
  int retrievePin;
  retrievePin = EEPROM.read(addr);
  Serial.print("My pin is:");
  Serial.print(retrievePin);
  Serial.println(".");
}

void loop()
{
 
}
