#include <ColorLCDShield.h>

#define BACKGROUND  BLACK
#define C_COLOR  RED
#define M_COLOR  GREEN

LCDShield lcd;

int buttonPins[5] = {A0, A1, A2, A3, A4};

void setup()
{
  /* Set up the button pins as inputs, set pull-up resistor */
  for (int i=0; i<5; i++)
  {
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
  }
  
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
  takeInput();  
  printString("Waiting...", 50,10);
}

void sayHello() {
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

void takeInput()
{
  if(!digitalRead(buttonPins[0]))
  {
    lcd.clear(BACKGROUND);
    printString("LAST INPUT: 0", 100, 0);
  }
  
  if(!digitalRead(buttonPins[1]))
  {
    lcd.clear(BACKGROUND);
    printString("LAST INPUT: 1", 100, 0);
  }
  
  if(!digitalRead(buttonPins[2]))
  {
    lcd.clear(BACKGROUND);
    printString("LAST INPUT: 2", 100, 0);
  }
  
  if(!digitalRead(buttonPins[3]))
  {
    lcd.clear(BACKGROUND);
    printString("LAST INPUT: 3", 100, 0);
  }
  
  if(!digitalRead(buttonPins[4]))
  {
    lcd.clear(BACKGROUND);
    printString("LAST INPUT: 4", 100, 0);
  }
  
  if(!digitalRead(buttonPins[5]))
  {
    lcd.clear(BACKGROUND);
    printString("LAST INPUT: 5", 100, 0);
  }
}
