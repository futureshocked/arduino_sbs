/*************************************************** 
  This sketch implements a simple door security system.

  It uses a fingerprint sensor for authentication.

  If there is a fingerprint match, it turns off the coil
  of a fail-safe electric door lock. This allows a person
  to enter or exit a room.

  Five seconds later, the door lock is energised and the
  door is locked again.

  Look at the Arduino SbS course at http://txplore.tv/courses/arduino-sbs
  for more information.
 ****************************************************/


#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(4, 5);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis;
const long lock_interval = 5000; //This is the amount of time I want the lock to remain open
const int lock_pin = 9;

void setup()  
{

  pinMode(lock_pin, OUTPUT);
  digitalWrite(lock_pin,HIGH); //This will keep the latch lock to HIGH
                        //and keep the door locked (until it goes LOW)
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  
  Serial.begin(9600);
  Serial.println("Adafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
}

void loop()                     // run over and over again
{
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.

   currentMillis = millis();
   //If enough time has passed since unlocking the door, lock it
   if (currentMillis - previousMillis >= lock_interval) 
      digitalWrite(lock_pin,HIGH); //lock the lock
}


// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  //IF there is a confident match, open the latch lock
  //and keep it open for the unlock interval
  if (finger.confidence > 50)
  {
    previousMillis = millis();    
    digitalWrite(lock_pin,LOW);  //open the lock
    }
  
  return finger.fingerID; 
}
