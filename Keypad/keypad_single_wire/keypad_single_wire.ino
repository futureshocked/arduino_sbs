char* keypressed;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard

void setup(){  
  Serial.begin(9600);  //hardware serial to PC  
}

void loop(){
 
 keyboardValue = analogRead(A0); // read the keyboard value (0 - 1023)

 while (keyboardValue < 5){  
   //do nothing until a key is pressed
   keyboardValue = analogRead(A0); 
   delay(50);
                            }
                            
                           
  readkeyboard(); //get the value of key being pressed "keypressed" i.e. 0-9 
}

//read the keyboard routine
void readkeyboard(){
   keyboardValue = analogRead((A0)); // read the value (0-1023)
    Serial.print("Pin value:");           
  Serial.println( keyboardValue);  
//   if (keyboardValue <25){keypressed = 0;}
   if ((keyboardValue >842) && (keyboardValue < 845)){keypressed = "1";}
   if ((keyboardValue >735) && (keyboardValue < 738)){keypressed = "2";}
   if ((keyboardValue >639) && (keyboardValue < 642)){keypressed = "3";}
   if ((keyboardValue >516) && (keyboardValue < 518)){keypressed = "4";}
   if ((keyboardValue >474) && (keyboardValue < 476)){keypressed = "5";}
   if ((keyboardValue >432) && (keyboardValue < 435)){keypressed = "6";}
   if ((keyboardValue >349) && (keyboardValue < 351)){keypressed = "7";}
   if ((keyboardValue >329) && (keyboardValue < 331)){keypressed = "8";}
   if ((keyboardValue >309) && (keyboardValue < 311)){keypressed = "9";}
   if ((keyboardValue >257) && (keyboardValue < 259)){keypressed = "0";}
    if ((keyboardValue >269) && (keyboardValue < 272)){keypressed = "*";}
    if ((keyboardValue >=245) && (keyboardValue < 247)){keypressed = "#";}
    if ((keyboardValue >598) && (keyboardValue < 600)){keypressed = "A";}
    if ((keyboardValue >416) && (keyboardValue < 419)){keypressed = "B";}
    if ((keyboardValue >303) && (keyboardValue < 305)){keypressed = "C";}
    if ((keyboardValue >242) && (keyboardValue < 245)){keypressed = "D";}
   if (keyboardValue >938){keypressed = 0;}
  //NOTE: the values used above are all halfway between the value obtained with each keypress in previous test sketch 
   
   while (keyboardValue > 25) {
     delay (100);
     keyboardValue = analogRead((A0)); // read the value (0-1023)
   }//wait until key no longer being pressed before continuing
        
   Serial.println(keypressed);      // print the value back to the Serial view window on your PC
   delay(1000);                     // wait 1000 milliseconds before the next loop
                     }
   //end of read the keyboard routine


