/*
  SD card datalogger
 
 This example shows how to log data from three analog sensors 
 to an SD card using the SD library.
 	
 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 	 
 */

#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 10;

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Wire.begin();

  rtc.begin();

//  if (! rtc.isrunning()) {
//    Serial.println("RTC is NOT running!");
//    rtc.adjust(DateTime(2014,01,16,14,45,00));
//    // following line sets the RTC to the date & time this sketch was compiled
//    //RTC.adjust(DateTime(__DATE__, __TIME__));
//  }
  
  rtc.adjust(DateTime(__DATE__, __TIME__));


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  DateTime now = rtc.now(); //get the time
  
  // make a string for assembling the data to log:
  String dataString = "";

  // read two sensors and append to the string:
  for (int analogPin = 0; analogPin < 2; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 1) {
      dataString += ","; 
    }
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    print_time(now, dataFile);
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
  delay(3000);
  
}

void print_time(DateTime capture_time, File file)
{
   file.print(capture_time.year(), DEC);
   file.print('/');
   file.print(capture_time.month(), DEC);
   file.print('/');
   file.print(capture_time.day(), DEC);
   file.print(' ');
   file.print(capture_time.hour(), DEC);
   file.print(':');
   file.print(capture_time.minute(), DEC);
   file.print(':');
   file.print(capture_time.second(), DEC);
   file.print(',');
}
