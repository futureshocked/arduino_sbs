#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp;
  
void setup() {  
  mcp.begin();  
  mcp.pinMode(7, OUTPUT);
}

void loop() {
  delay(100);
  mcp.digitalWrite(7, HIGH);
  delay(100);
  mcp.digitalWrite(7, LOW);
}
