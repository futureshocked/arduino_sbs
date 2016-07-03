/*
This sketch is used to demonstrated the EasyDriver motor controller board with 
a NEMA17 stepper motor.

For more informaiton on the EasyDriver, please go to http://www.schmalzhaus.com/EasyDriver/

More examples to help you learn the details of the EasyDriver are here: http://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html

*/


void setup() {                
  pinMode(8, OUTPUT);     
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void loop() {
  digitalWrite(8, LOW);  
  for (int i=0;i<800;i++)
  {
  
  digitalWrite(9, HIGH);
  delay(1);          
  digitalWrite(9, LOW); 
  delay(1); 
  }
  digitalWrite(8, HIGH);  
  
  for (int i=0;i<800;i++)
  {
    digitalWrite(9, HIGH);
    delay(1);          
    digitalWrite(9, LOW); 
    delay(1); 
  }
}
