/*
HC-SR04 Ping distance sensor]
Temperature Sensor TMP36
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 12 Trig to Arduino pin 13
Red POS to Arduino pin 11
Green POS to Arduino pin 10
Analog 0 to TMP36
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
Additional code added to adjust speed of sound based on temperature modified from SparkFun code

*/

// We'll use analog input 0 to measure the temperature sensor's
// signal pin.

const int temperaturePin = 0; 

#define trigPin 13
#define echoPin 12

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  float voltage, degreesC, degreesF, speedOfSound;

  // First we'll measure the voltage at the analog pin. Normally
  // we'd use analogRead(), which returns a number from 0 to 1023.
  // Here we've written a function (further down) called
  // getVoltage() that returns the true voltage (0 to 5 Volts)
  // present on an analog input pin.

  voltage = getVoltage(temperaturePin);
  
  // Now we'll convert the voltage to degrees Celsius.
  // This formula comes from the temperature sensor datasheet:

  degreesC = (voltage - 0.5) * 100.0;
  
  // While we're at it, let's convert degrees Celsius to Fahrenheit.
  // This is the classic C to F conversion formula:
  
  degreesF = degreesC * (9.0/5.0) + 32.0;
    
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  speedOfSound = (degreesC * 0.6 + 331.5)/10000;
  distance = (duration/2) * speedOfSound; //includes Speed of Sound conversion factor into centimeters and micro seconds

  if (distance >= 200 || distance <= 0){
    Serial.print("  deg C: ");
    Serial.print(degreesC);
    Serial.print("   ");
    Serial.print(speedOfSound);
    Serial.println("Out of range");
    
  }
  else {
    Serial.print("  deg C: ");
    Serial.print(degreesC);
    Serial.print("   ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}


float getVoltage(int pin)
{

  return (analogRead(pin) * 0.004882814);
}
