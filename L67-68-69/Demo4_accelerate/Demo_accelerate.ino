#include <AccelStepper.h>

#define MOTORWIRES 4

// motor pins
#define motorPin1  8     
#define motorPin2  9     
#define motorPin3  10    
#define motorPin4  11    
                        
// NOTE: The sequence 1-3-2-4 is required for proper sequencing of 28BYJ48
AccelStepper stepper1(MOTORWIRES, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(50.0);
  stepper1.setSpeed(200);
  stepper1.moveTo(2048);  // 1 revolution = 48*64
}


void loop()   
{
  //Change direction at the limits
  if (stepper1.distanceToGo() == 0) 
    stepper1.moveTo(-stepper1.currentPosition());

  
  stepper1.run();

}
