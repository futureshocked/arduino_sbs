#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper(1, 9, 8);

int pos = 5000;

void setup()
{  
  stepper.setMaxSpeed(4000);
  stepper.setAcceleration(500);
}

void loop()
{
  if (stepper.distanceToGo() == 0)
  {
    stepper.setSpeed(5000);
    delay(500);
    pos = -pos;
    stepper.moveTo(pos);
  }
  stepper.run();
}
