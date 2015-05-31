#include <TimerOne.h>

int ledPin = 13;
volatile int ledState = HIGH;

void setup()
{
  pinMode(13, OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(toggleLED); 
}

void loop(){
}

void toggleLED()
{
  digitalWrite(ledPin, ledState);
  ledState = !ledState; 
}
