#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);//, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup()
{
    lcd.begin(16,2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello world!");
    lcd.setCursor(0, 1);
    lcd.print("Row number: ");
    lcd.setCursor(12, 1);
    lcd.print("2");
}
void loop()
{
 
}
