/*
Pushbutton sketch
a switch connected to pin 2 lights the LED on pin 13
*/
const int ledPin = 13; 
const int inputPin = 2;

void setup() { 
  pinMode(ledPin, OUTPUT);
// choose the pin for the LED
// choose the input pin (for a pushbutton)
// declare LED as output
// declare pushbutton as input
pinMode(inputPin, INPUT);
}


void loop()
  {
    int val = digitalRead(inputPin); // read input value
    if (val == HIGH)
    {
      digitalWrite(ledPin,HIGH);
    } else
    {
      digitalWrite(ledPin,LOW); 
    }
  } 

