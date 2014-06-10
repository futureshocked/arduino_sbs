/*
Pushbutton interrupt sketch
a switch connected to interrupt pin 2 lights the LED on pin 13
*/
const int ledPin = 13; 
const int inputPin = 2;

void setup() { 
  pinMode(ledPin, OUTPUT);
  attachInterrupt(0,buttonPressed,FALLING);
}

void loop()
  {  
  } 
  
void buttonPressed()
{
  if (digitalRead(ledPin))
      digitalWrite(ledPin,LOW); 
  else
      digitalWrite(ledPin,HIGH); 
}


