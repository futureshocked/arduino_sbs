 struct Morse
{
   char character;
   String  code;
};

int dot_length_ms = 50; //The duration of a dot
int dash_legth = 3 * dot_length_ms; // One dash is three dots
int part_gap = 1 * dot_length_ms; // Space between parts of a letter is one dot
int letter_space = 3 * dot_length_ms; // Space between letters 
int words_space = 7 * dot_length_ms; // Space between words


#define led_pin 13
#define total_morse_code_items 36
Morse codes[total_morse_code_items] = {
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



void setup() {
  // initialize digital pin 13 as an output.
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);


  String text_to_send = "HELLO WORLD";
  Serial.println("Starting...");
  transmit(text_to_send);

}

// the loop function runs over and over again forever
void loop() {
}

void transmit(String text_to_send)
{
  //For each letter, find its code and transmit it
  for (int letter = 0; letter < text_to_send.length(); letter++)
  {
    int code_index = 0;
    for (int i = 0; i < total_morse_code_items; i++)
    {
       if (codes[i].character == text_to_send[letter])
       {
         code_index = i;
         break; 
       }
    }
   
    
    //Make flashes for letter at index code_index
    
    for (int i = 0; i < codes[code_index].code.length(); i++)
    {
//      Serial.print(codes[code_index].code[i]);
      flash_led(codes[code_index].code[i]);
//      Serial.print("   "); //Space in between letters is three units
    }
//    Serial.print(" "); //Space in between words is three units
      flash_led(' '); //Space in between words is three units
  }
}

void flash_led(char code)
{
    digitalWrite( led_pin, HIGH);
    if (code == '.')         
         delay(dot_length_ms);
    else if (code == ' ') 
        delay(words_space);
    else
       delay(dash_legth);
       
     digitalWrite( led_pin, LOW);
     delay(letter_space);
}


