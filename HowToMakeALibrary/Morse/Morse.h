// Morse library
// 10/3/2015 by Peter Dalmaris <peter@txplore.com>
// Source repository: https://github.com/futureshocked/arduino_sbs/tree/master/HowToMakeALibrary/Morse


/* ============================================
Morse library code is placed under the MIT license
Copyright (c) 2015 Peter Dalmaris

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef Morse_h
#define Morse_h

#include <Arduino.h>

 struct Morse_codes
{
   char character;
   String  code;
};

#define TOTAL_MORSE_CODE_ITEMS 36
static Morse_codes codes[TOTAL_MORSE_CODE_ITEMS] = {
                    {'A',".-"},
                    {'B',"-..."},
                    {'C',"-.-."},
                    {'D',"-.."},
                    {'E',"."},
                    {'F',"..-."},
                    {'G',"--."},
                    {'H',"...."},
                    {'I',".."},
                    {'K',"-.-"},
                    {'L',".-.."},
                    {'M',"--"},
                    {'N',"-."},
                    {'O',"---"},
                    {'P',".--."},
                    {'Q',"--.-"},
                    {'R',".-."},
                    {'S',"..."},
                    {'T',"-"},
                    {'U',"..-"},
                    {'V',"...-"},
                    {'W',".--"},
                    {'X',"-..-"},
                    {'Y',"-.--"},
                    {'Z',"--.."},
                    {'1',".----"},
                    {'2',"..---"},
                    {'3',"...--"},
                    {'4',"....-"},
                    {'5',"....."},
                    {'6',"-...."},
                    {'7',"--..."},
                    {'8',"---.."},
                    {'9',"----."},
                    {'0',"-----"},
                    {' ',}
                    };

  class Morse
  {
   private:
      int _dot_length_ms;        //The duration of a dot
      int _dash_legth;           // One dash is three dots
      int _part_gap;             // Space between parts of a letter is one dot
      int _letter_space;         // Space between letters 
      int _words_space;          // Space between words
      int _led_pin;              // The LED pin
      void flash_led(char code); // Actual flashing happens here
    
   public:
      Morse();                   //sets up the Morse object with default settings
      Morse(int dot_duration);   //sets up the Morse object with custom dot duration
      Morse(int dot_duration, int LED_pin);   //sets up the Morse object with custom dot duration and LED pin
      void transmit(String text_to_transmit); // Converts text to morse code and transmits it  
  };

#endif
