
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
