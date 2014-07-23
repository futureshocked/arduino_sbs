
//Arduino SbS 
//Create a random pattern of blinking LED
//Using a seven segment display

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 9;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 10;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 8;

const byte CHAR_COUNT = 10;
const byte symbols[CHAR_COUNT] = {
B10000001, // 0
B11111111, // 1
B11111111, // 2 
B11111111, // 3
B11111111, // 4 
B11111111, // 5
B11111111, // 6 
B11111111, // 7
B11111111, // 8 
B11111111  // 9
};



void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  writeLeds(symbols[0]);
}

void loop() {

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


