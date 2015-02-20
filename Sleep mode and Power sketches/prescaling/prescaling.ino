#include <Prescaler.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  setClockPrescaler(CLOCK_PRESCALER_256);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13,HIGH);
  trueDelay(5000);
  digitalWrite(13,LOW);
  trueDelay(5000);
}
