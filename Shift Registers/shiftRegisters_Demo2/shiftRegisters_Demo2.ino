
//Arduino SbS Lecture 60 Demo 2
//Create a random pattern of blinking LED
//Using a total of 16 LEDs

//Please double-check your wiring for the latch, clock and data pins.
//If you constructed your circuit exactly as shown in the schematic in the video,
//use the following definitions:
//Pin connected to latch pin (ST_CP) of 74HC595
// const int latchPin = 9;
//Pin connected to clock pin (SH_CP) of 74HC595
// const int clockPin = 10;
////Pin connected to Data in (DS) of 74HC595
// const int dataPin = 8;

//If you did the wiring based on the demo, please use these definitions instead:
//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;     
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
//Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void loop() {
  byte randNumber1 = random(255);
  byte randNumber2 = random(255);
  writeLeds(randNumber1);
  writeLeds(randNumber2);
  delay(100);  
}

void writeLeds(byte pattern)
{
  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);
  // turn on the next highest bit in bitsToSend:
  Serial.println(pattern,BIN);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, pattern);

  // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
  }


