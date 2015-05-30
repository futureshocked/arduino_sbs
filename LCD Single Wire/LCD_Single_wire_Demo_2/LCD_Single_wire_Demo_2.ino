// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity

RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16,2);
  lcd.backlight();
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop () {
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    //Show the time on the screen
    
    lcd.setCursor(0, 0);
    lcd.print(now.year(), DEC);
    lcd.print('/');
    if (now.month()<10)
    { lcd.print("0"); }
    lcd.print(now.month(), DEC);
    lcd.print('/');
    if (now.day()<10)
    { lcd.print("0"); }
    lcd.print(now.day(), DEC);
    lcd.setCursor(0, 1);
    if (now.hour()<10)
    { lcd.print("0"); }
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    if (now.minute()<10)
    { lcd.print("0"); }
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    if (now.second()<10)
    { lcd.print("0"); }
    lcd.print(now.second(), DEC);   

    delay(100);
}
