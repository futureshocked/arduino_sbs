/*
 * PIR sensor tester
 */
 
int ledPin = 13;       // choose the pin for the LED
int inputPin = 3;      // choose the input pin (for PIR sensor)
int pirState = true;    // we start, assuming no motion detected
int val = 0;           // variable for reading the pin status
int minimummSecsLowForInactive = 5000; // If the sensor reports low for
                       // more than this time, then assume no activity
long unsigned int timeLow;                  
boolean takeLowTime;  

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;  
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
  
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState) {
      // we have just turned on
      pirState = false;
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      delay(50);
    }
   takeLowTime = true;
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    
    if (takeLowTime){
      timeLow = millis();
      takeLowTime = false;
    }
    
    if(!pirState && millis() - timeLow > minimummSecsLowForInactive){
     pirState = true; 
     Serial.println("Motion ended!");     
     delay(50);
    }
    
  }
}

