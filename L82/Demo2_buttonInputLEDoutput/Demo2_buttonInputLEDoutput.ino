#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp;
  
void setup() {  
  mcp.begin();      // use default address 0
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(0, INPUT);
}



void loop() {
  mcp.digitalWrite(7, mcp.digitalRead(0));
}
