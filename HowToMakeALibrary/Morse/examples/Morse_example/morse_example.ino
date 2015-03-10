#include <Morse.h>

//Morse morse = Morse(); //Just use defaults
//Morse morse = Morse(50); //Specify the dot duration
Morse morse = Morse(20,13); //Specify the dot duration and LED pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  morse.transmit("HELLO WORLD");
}

void loop() {
  // put your main code here, to run repeatedly:
}
