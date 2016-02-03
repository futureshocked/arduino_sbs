int pwmPin = 9;
int potPin = A0;
int analogValue = 0;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(pwmPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogValue = map(analogRead(potPin), 0,1024,0,255);
  analogWrite(pwmPin, analogValue );

  delay(50);
}
