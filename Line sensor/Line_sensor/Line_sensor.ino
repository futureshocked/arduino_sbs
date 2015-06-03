// Line Sensor Breakout - Analog

int out;
#define tiltPin 12;

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
  pinMode(tiltPin, INPUT);

}

void loop()
{
  out = digitalRead(0);       // read analog input pin 0
  
  Serial.println(out, DEC);    // print the state of the digital pin 0

  delay(100);              // wait 100ms for next reading
}

