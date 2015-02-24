#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )

Max72xxPanel matrix = Max72xxPanel(pinCS, 1, 1);

int x, y;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);      
     matrix.setIntensity(0);
}

void loop() {
  x = analogRead(0);       // read analog input pin 0
  y = analogRead(1);       // read analog input pin 1
  Serial.print("accelerations are x, y: ");
  Serial.print(x, DEC);      
  Serial.print(" ");         
  Serial.println(y, DEC);    
  
  int matrix_y = map(y, 377, 476, 7, 0);
  int matrix_x = map(x, 382, 479, 7, 0);
  
  matrix.fillScreen(0);   //Clear the screen
  matrix.drawPixel(matrix_x, matrix_y, HIGH);
  matrix.write();         // Send bitmap to display
  delay(50);              // wait 50ms for next reading
}
