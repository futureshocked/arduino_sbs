/*
Pushbutton interrupt sketch
a switch connected to interrupt pin 2 lights the LED on pin 13
A volatile counter keeps track of button presses.
*/
const int ledPin = 13; 
const int inputPin = 2;
volatile byte counter = 0;

void setup() { 
  pinMode(ledPin, OUTPUT);
  attachInterrupt(0,buttonPressed,FALLING);
  Serial.begin(9600);
}

void loop()
  {  
  } 
  
void buttonPressed()
{
  counter++;
  Serial.println(counter, DEC);
  if (digitalRead(ledPin))
      digitalWrite(ledPin,LOW); 
  else
      digitalWrite(ledPin,HIGH); 
}


