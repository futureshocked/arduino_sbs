
//Arduino SbS 
//Create a random pattern of blinking LED
//Using a seven segment display

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 9;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 10;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 8;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void loop() {
  pattern1();
  delay(100);  
}

void pattern1()
{
  byte randNumber1 = random(255);
  writeLeds(randNumber1);
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


