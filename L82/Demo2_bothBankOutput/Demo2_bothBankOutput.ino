#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp;
  
void setup() {  
  mcp.begin();      // use default address 0
  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(7, OUTPUT);
}


// flip the pin #0 up and down

void loop() {
  delay(100);
  mcp.digitalWrite(8, HIGH);
  mcp.digitalWrite(7, HIGH);
  delay(100);
  mcp.digitalWrite(8, LOW);
  mcp.digitalWrite(7, LOW);
}
