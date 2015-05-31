#include <TimerOne.h>

int ledPin = 9;

void setup()
{
    Timer1.initialize(1000);
    Timer1.pwm(ledPin,0);
    pinMode(ledPin, OUTPUT);
}

void loop(){
    Timer1.setPwmDuty(ledPin, 250);
    delay(1000);
    Timer1.setPwmDuty(ledPin, 500);
    delay(1000);
    Timer1.setPwmDuty(ledPin, 800);
    delay(1000);
    Timer1.setPwmDuty(ledPin, 1024);
    delay(1000);
}



