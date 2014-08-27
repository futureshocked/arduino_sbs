// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

int ledpin = 8;
int buttonPin = 7;
float h;
float t;
long lastReading = millis();

void setup() {
  Serial.begin(38400);
  Serial.println("DHT test");
  pinMode(ledpin, OUTPUT);
  pinMode(buttonPin, INPUT);
  dht.begin();
}

void loop() {
  if (millis() - lastReading > 10000)
      {
        getSensorReadings();
        lastReading = millis();
      }

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("-1");
  } else {
    Serial.print(t);
    Serial.print(",");
    Serial.print(h);
  }
  
  Serial.print(",");
  Serial.print(analogRead(A0));
  Serial.print(",");
  Serial.print(digitalRead(buttonPin));
  Serial.println();
  
  char val = Serial.read();
  if( val == 'A' || val == 'a' )               // if 'H' was received
  {
    digitalWrite(ledpin, HIGH);  // turn ON the LED
  } 
  if ( val == 'B' || val == 'b' ) { 
    digitalWrite(ledpin, LOW);   // otherwise turn it OFF
  }
  

}

void getSensorReadings()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
}
