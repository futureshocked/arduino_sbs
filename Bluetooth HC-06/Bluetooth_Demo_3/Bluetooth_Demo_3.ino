#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

char val; // variable to receive data from the serial port
int ledpin = 8; // LED connected to pin 8 (on-board LED)

int sensorpin = 0; //Analog pin

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 1000;


void setup() {

  pinMode(ledpin, OUTPUT);  // pin 8 (on-board LED) as OUTPUT
  
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() {

  if( mySerial.available() )       // if data is available to read
  {
    val = mySerial.read();         // read it and store it in 'val'
  }
  if( val == 'H' )               // if 'H' was received
  {
    digitalWrite(ledpin, HIGH);  // turn ON the LED
  } else { 
    digitalWrite(ledpin, LOW);   // otherwise turn it OFF
  }
  delay(100);                    // wait 100ms for next reading
  
  if((millis() - lastConnectionTime > postingInterval)) {
            int ana_A = analogRead(sensorpin);
            mySerial.print("Sensor reading: ");
            mySerial.println(ana_A);
            lastConnectionTime = millis();
  }
} 
