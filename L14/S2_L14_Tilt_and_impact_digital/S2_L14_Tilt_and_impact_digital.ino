// Line Sensor Breakout - Analog

int out;
#define tiltPin 12

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
  pinMode(tiltPin, INPUT);

}

void loop()
{
  out = digitalRead(tiltPin);       // read analog input pin 0

  
  Serial.println(out, DEC);    // print the acceleration in the X axis

  delay(100);              // wait 100ms for next reading
}

