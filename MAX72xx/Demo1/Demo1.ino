#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )

Max72xxPanel matrix = Max72xxPanel(pinCS, 1, 1);

void setup() {
  matrix.setIntensity(4); // Set brightness between 0 and 15

}

void loop() {
  // Dots
  matrix.fillScreen(0);      //This will fill the display. The parameter controls the colour.
                             // 0: is blank (or black clears display), 1: is white (or lit)
  matrix.drawPixel(0, 0, 1); // Draws a single pixel at position X 0 and Y 0. Color is 1.
                             // This function draws in a buffer, not directly to the display.
                             // You can do some more drawing to the buffer, and then...
  matrix.drawPixel(3, 4, 1);                           
  matrix.write();            // Draws the buffer to the display.
  
  delay(500);

  matrix.fillScreen(0);  
  matrix.drawPixel(7, 7, 1);
  matrix.write();

  delay(500);
  
  //Lines
  matrix.fillScreen(0);    
  for (int i=0;i<8;i++)             // This loop produces a moving line from 
  {                                 // top to bottom
    matrix.drawLine(0, i, 7, i, 1); //Draws a line between two coordinates
    matrix.write();
    delay(40);
    matrix.fillScreen(0);    
  }
  for (int i=0;i<8;i++)             // This loop produces a moving line from 
  {                                 // left to right
    matrix.drawLine(i, 0, i, 7, 1);
    matrix.write();
    delay(40);
    matrix.fillScreen(0);    
  }
  for (int i=7;i>=0;i--)            // This loop produces a moving line from 
  {                                 // bottom to top
    matrix.drawLine(0, i, 7, i, 1);
    matrix.write();
    delay(40);    matrix.fillScreen(0);    
  }
  for (int i=7;i>=0;i--)            // This loop produces a moving line from 
  {                                 // right to left
    matrix.drawLine(i, 0, i, 7, 1);
    matrix.write();
    delay(40);
    matrix.fillScreen(0);    
  }
  
  for (int i=0;i<8;i++)
  {                                 // This loop produces a moving line that
    matrix.drawLine(4, 4, i, 0, 1); // covers the top quadrant
    matrix.write();
    delay(40);
    matrix.fillScreen(0);    
  }

  for (int i=0;i<8;i++)             // This loop produces a moving line that
  {                                 // covers the right quadrant
    matrix.drawLine(4, 4, 7, i, 1);
    matrix.write();
    delay(40);
    matrix.fillScreen(0);    
  }
  
  for (int i=7;i>=0;i--)            // This loop produces a moving line that
  {                                 // covers the bottom quadrant
    matrix.drawLine(4, 4, i, 7, 1);
    matrix.write();
    delay(40);
    matrix.fillScreen(0);    
  }
  
  for (int i=7;i>=0;i--)            // This loop produces a moving line that
  {                                 // covers the left quadrant
    matrix.drawLine(4, 4, 0, i, 1);
    matrix.write();
    delay(40);
    matrix.fillScreen(0);    
  }

  
  //Rectangles
  for (int i=0;i<5;i++)                // This loop produces a box that
  {                                    // shrinks
  matrix.fillScreen(0);    
  matrix.drawRect(i,i,8-i*2,8-i*2,1);
  matrix.write();
  delay(40);
  }
  delay(500);

  //Circle
  for (int i=0;i<4;i++)              // This loop produces a circle that
  {                                  // shrinks
  matrix.fillScreen(0);    
  matrix.drawCircle(4,4,i,1);
  matrix.write();
  delay(40);
  }
  delay(500);

  //Triangle
  for (int i=0;i<8;i++)                // This loop produces a triangle that
  {                                    // has one apex moving
  matrix.fillScreen(0);      
  matrix.drawTriangle(i,i,0,7,7,0,1);
  matrix.write();
  delay(40);
  }
  for (int i=7;i>=0;i--)
  {
  matrix.fillScreen(0);      
  matrix.drawTriangle(i,i,0,7,7,0,1);
  matrix.write();
  delay(40);
  }
  delay(500);
  
  //Filled Triangle                    // Like above, but the triangle is filled
  for (int i=0;i<8;i++)
  {
  matrix.fillScreen(0);      
  matrix.fillTriangle(i,i,0,7,7,0,1);
  matrix.write();
  delay(40);
  }
  for (int i=7;i>=0;i--)
  {
  matrix.fillScreen(0);      
  matrix.fillTriangle(i,i,0,7,7,0,1);
  matrix.write();
  delay(40);
  }
  delay(500);
  
  //Draw Text
 String my_string = "Tech Explorations!";   // This text will be displayed, a letter a time
 for (int i = 0; i<my_string.length(); i++) // Loop through the contents of the string
 {
  matrix.fillScreen(0);                     // Clear the display before showing the next char
  matrix.drawChar(0,0,my_string[i],1,0,1);  // Draw a char to the buffer
  matrix.write();                           // Draw the buffer to the display
  delay(500);
 }
 
 //Draw scrolling text
 int spacer = 1;                            // This will scroll the string
 int width = 5 + spacer;                    // The font width is 5 pixels
 for ( int i = 0 ; i < width * my_string.length() + width - 1 - spacer; i++ ) {

    matrix.fillScreen(0);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < my_string.length() ) {
        matrix.drawChar(x, y, my_string[letter], 1, 0, 1);
      }

      letter--;
      x -= width;
    }

    matrix.write(); // Send bitmap to display

    delay(100);
  }
  
  /********************/
  //Brightness
  for (int i=0; i<16; i++)
  {
  matrix.setIntensity(i);
  matrix.fillScreen(i);
  matrix.write(); //send bitmap to display
  delay(200);
  }
  /********************/
}
