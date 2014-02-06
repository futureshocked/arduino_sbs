char val; // variable to receive data from the serial port
int ledpin = 8; // LED connected to pin 48 (on-board LED)

void setup() {

  pinMode(ledpin, OUTPUT);  // pin 8 (on-board LED) as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
}

void loop() {

  if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();         // read it and store it in 'val'
  }
  if( val == 'H' )               // if 'H' was received
  {
    digitalWrite(ledpin, HIGH);  // turn ON the LED
  } else { 
    digitalWrite(ledpin, LOW);   // otherwise turn it OFF
  }
  delay(100);                    // wait 100ms for next reading
} 
