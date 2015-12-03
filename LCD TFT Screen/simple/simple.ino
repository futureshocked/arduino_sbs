/*
  ChronoLCD Color - An example sketch for the Color LCD Shield Library
  by: Jim Lindblom
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute. Let me know if you make hugely, awesome, great changes.
  
  This sketch draws an analog and digital clock on the Color LCD
  Shield. You can also use the on-board buttons to set the hours
  and minutes.
  
  Use the defines at the top of the code to set the initial time.
  You can also adjust the size and color of the clock.
  
  To set the time, first hit S3. Then use S1 and S2 to adjust the
  hours and minutes respsectively. Hit S3 to start the clock
  back up.
  
  This example code should give you a good idea of how to use
  the setCircle, setLine, and setStr functions of the Color LCD
  Shield Library.
*/
#include <ColorLCDShield.h>

#define BACKGROUND  BLACK  // room for growth, adjust the background color according to daylight
#define C_COLOR  RED  // This is the color of the clock face, and digital clock
#define H_COLOR  BLUE  // hour hand color
#define M_COLOR  GREEN  // minute hand color
#define S_COLOR  YELLOW  // second hand color

LCDShield lcd;


int buttonPins[3] = {A0, A1, A2};  //You can add A3 ,A4 for button

void setup()
{
  /* Set up the button pins as inputs, set pull-up resistor */
  for (int i=0; i<3; i++)
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
  /* We'll run around checking for button presses, 
     until it's been a second */

  
  lcd.setStr("Testing - Line 1", 0, 0, M_COLOR, BACKGROUND);
  lcd.setStr("Testing - Line 2", 20, 0, M_COLOR, BACKGROUND);
}

