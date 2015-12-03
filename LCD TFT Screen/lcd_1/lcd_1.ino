#include <ColorLCDShield.h>

#define BACKGROUND  BLACK  // background color
#define C_COLOR  RED       // red color constant
#define M_COLOR  GREEN     // green color constant

LCDShield lcd;

void setup()
{  
  pinMode(10, OUTPUT);
  analogWrite(10, 255); //PWM control blacklight
  /* Initialize the LCD, set the contrast, clear the screen */
  lcd.init(PHILLIPS);
  lcd.contrast(40);
  lcd.clear(BACKGROUND);
  lcd.setStr("STARTING", 50, 0, C_COLOR, BACKGROUND);
  delay(1000);
  lcd.clear(BACKGROUND);
}

void loop()
{
 
  char* Str4[ ] = {"arduino 1","arduino 2","arduino 3"};

  for (int i=0;i<3;i++)
   {
     printString(Str4[i], 15 * i,0);
   }
}

void printString(char* toPrint, int x, int y)
{
      lcd.setStr(toPrint, x, y, M_COLOR, BACKGROUND);
}
