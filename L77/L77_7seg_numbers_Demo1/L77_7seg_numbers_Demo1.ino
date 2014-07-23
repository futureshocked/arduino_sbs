
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
B11101101, // 1
B01000011, // 2 
B01001001, // 3
B00101101, // 4 
B00011001, // 5
B00010001, // 6 
B11001101, // 7
B00000001, // 8 
B00001001  // 9
};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pattern1();


}

void pattern1()
{
  int i=0;
  while(i<CHAR_COUNT)
  {
    Serial.print(i);
    Serial.print(" - ");
    Serial.print(symbols[i],BIN);
    Serial.print(" ");
    Serial.print(symbols[i+1],BIN);
    writeLeds(symbols[i]);
    i = i+1;    
    delay(500);  
  }
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


