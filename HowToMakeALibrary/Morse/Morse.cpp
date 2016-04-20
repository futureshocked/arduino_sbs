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

#include <Morse.h>
#include <Arduino.h>

//Create the constructors
Morse::Morse()
{
  _dot_length_ms  = 50;                 //The duration of a dot
  _dash_legth     = 3 * _dot_length_ms; // One dash is three dots
  _part_gap       = 1 * _dot_length_ms; // Space between parts of a letter is one dot
  _letter_space   = 3 * _dot_length_ms; // Space between letters 
  _words_space    = 7 * _dot_length_ms; // Space between words
  _led_pin        = 13;
  pinMode(_led_pin, OUTPUT);
}

Morse::Morse(int dot_duration)
{
  _dot_length_ms  = dot_duration;       //The duration of a dot
  _dash_legth     = 3 * _dot_length_ms; // One dash is three dots
  _part_gap       = 1 * _dot_length_ms; // Space between parts of a letter is one dot
  _letter_space   = 3 * _dot_length_ms; // Space between letters 
  _words_space    = 7 * _dot_length_ms; // Space between words
  _led_pin        = 13;
  pinMode(_led_pin, OUTPUT);

}

Morse::Morse(int dot_duration, int led_pin)
{
  _dot_length_ms  = dot_duration;       //The duration of a dot
  _dash_legth     = 3 * _dot_length_ms; // One dash is three dots
  _part_gap       = 1 * _dot_length_ms; // Space between parts of a letter is one dot
  _letter_space   = 3 * _dot_length_ms; // Space between letters 
  _words_space    = 7 * _dot_length_ms; // Space between words
  _led_pin        = led_pin;
  pinMode(_led_pin, OUTPUT);
}

void Morse::transmit(String text_to_transmit)
{
  //For each letter, find its code and transmit it
  for (int letter = 0; letter < text_to_transmit.length(); letter++)
  {
    int code_index = 0;
    for (int i = 0; i < TOTAL_MORSE_CODE_ITEMS; i++)
    {
       if (codes[i].character == text_to_transmit[letter])
       {
         code_index = i;
         break; 
       }
    }
    Serial.print(text_to_transmit[letter]);
    Serial.print("-->");
    //Make flashes for letter at index code_index    
    for (int i = 0; i < codes[code_index].code.length(); i++)
    {      
      Serial.print(codes[code_index].code[i]);
      flash_led(codes[code_index].code[i]);

    }
      flash_led(' '); //Space in between words is three units
      Serial.println();
  }
}

void Morse::flash_led(char code)
{
    digitalWrite( _led_pin, HIGH);
    if (code == '.')         
        delay(_dot_length_ms);
    else if (code == ' ') 
        delay(_words_space);
    else
        delay(_dash_legth);
       
    digitalWrite( _led_pin, LOW);
    delay(_letter_space);
}
