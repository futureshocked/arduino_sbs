/*
  Read Analog Value
  Reads an analog input on pin 0.
  Attach a photoresistor to the breadboard, in series with a resistor (around 220 Ohm). 
  Connect one pin of the photoresistor to GND, one pin of the resistor to 5V. 
  Connect the photoresistor/resistor common pin to A0.
  You can also remove the photoresistor and resistor and replace it with a potentiometer.
  Connect it so that the middle pin is connected to A0, and the other two to 5V and GND 
  (it doesn't matter which pin goes to which voltage).
 
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(10);
}
