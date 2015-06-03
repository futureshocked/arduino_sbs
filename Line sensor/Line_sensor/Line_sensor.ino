// Line Sensor Breakout - Analog

int out;

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  out = analogRead(0);       // read analog input pin 0
  Serial.println(out, DEC);    // print the value of the analog pin 0
  delay(100);              // wait 100ms for next reading
}

