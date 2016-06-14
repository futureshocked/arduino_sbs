//Original sketch: https://bigdanzblog.wordpress.com/2014/08/16/using-a-ky040-rotary-encoder-with-arduino/
//Modified by Peter Dalmaris, July 2015


const int PinCLK=2;                   // Used for generating interrupts using CLK signal
const int PinDT=3;                    // Used for reading DT signal
const int PinSW=8;                    // Used for the push button switch

volatile long     virtualPosition  =0;  // must be volatile to work with the isr

void isr0 ()  {
  detachInterrupt(0);
  static unsigned long                lastInterruptTime = 0;
  unsigned long                       interruptTime = millis();
  // If interrupts come faster than 5ms, assume it's a bounce and ignore
  if (interruptTime - lastInterruptTime > 5) {
      if (!digitalRead(PinDT))
          virtualPosition++; 
      else
          virtualPosition--; 
      }
  lastInterruptTime = interruptTime;
  attachInterrupt (0,isr0,RISING);
  } // ISR0

void setup ()  {
  pinMode(PinCLK,INPUT);
  pinMode(PinDT,INPUT);  
  pinMode(PinSW,INPUT);
  attachInterrupt (0,isr0,RISING);   // interrupt 0 is always connected to pin 2 on Arduino UNO
  Serial.begin (9600);
  Serial.println("Start");
}

void loop ()  {
 
  int lastCount = 0;
  while (true) {
      if (!(digitalRead(PinSW))) {        // check if pushbutton is pressed
        virtualPosition = 0;            // if YES, then reset counter to ZERO
        while (!digitalRead(PinSW)) {}  // wait til switch is released
        delay(10);                      // debounce
        Serial.println("Reset");        // Using the word RESET instead of COUNT here to find out a buggy encoder
        }
      if (virtualPosition != lastCount) {
        lastCount = virtualPosition;
        Serial.print("Count:");
        Serial.println(virtualPosition);
        }
   } // while
}
