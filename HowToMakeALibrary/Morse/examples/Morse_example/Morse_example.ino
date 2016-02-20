// Morse library example
// 10/3/2015 by Peter Dalmaris <peter@txplore.com>
// Source repository: https://github.com/futureshocked/arduino_sbs/tree/master/HowToMakeALibrary/Morse

#include <Morse.h>

//Morse morse = Morse(); //Just use defaults
//Morse morse = Morse(50); //Specify the dot duration
Morse morse = Morse(20,13); //Specify the dot duration and LED pin

void setup() {
  Serial.begin(9600);
  morse.transmit("HELLO WORLD");
}

void loop() {
}
