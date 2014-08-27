 // Processing demo sketch
 
 // This program creates a simple bar graph
 // by getting data from a a DHT sensor and a
 // potentiometer running on
 // an Arduino. It also receives button status
 // data, and sends text input to the Arduino 
 // where an LED is controlled.
 
 // Created 18 August 2014
 // by Peter Dalmaris
 // This example code is in the public domain.
 
 import processing.serial.*;
 
 Serial myPort;        // The serial port
 
 void setup () {
 // set the window size:
 size(250, 400);      

 myPort = new Serial(this, "/dev/tty.usbmodem3d11", 38400);
 // don't generate a serialEvent() unless you get a newline character:
 myPort.bufferUntil('\n');
 // set inital background:
 background(0);
 }
 void draw () {
   if (keyPressed) {
    if (key == 'a' || key == 'A') {
      fill(0,0,0);
      rect(0,60,249,25);
      myPort.write('A');
      fill(204, 102, 0);
      textSize(18);
      text("LED ON", 10, 80);
      print("LED ON");
    }
    if (key == 'b' || key == 'B') {
      fill(0,0,0);
      rect(0,60,249,25);
      myPort.write('B');
      fill(204, 102, 0);
      textSize(18);
      text("LED OFF", 10, 80);
      print("LED OFF");
    }
  }
 }
 
 void serialEvent (Serial myPort) {
   // get the ASCII string:
   String inString = myPort.readStringUntil('\n');
//   print("inString:");
//   print(inString);
   if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    String[] q = splitTokens(inString,",");
 
    if (q.length == 4) {      
       float t = float(q[0]);
       float h = float(q[1]);
       float pot = int(q[2]);
       int button = int(q[3]);
//       print(button);

       float x = map(t, 0, 40, 0, 250);
       float y = map(h, 0, 100, 0, 250);
       pot = map(pot, 0, 1024, 0, 250);

//        print("x");print(x);
//        print("y");print(y);
       fill(0,0,0);
       rect(0,150,249,249);
       stroke(204, 102, 0);
       fill(153);
       rect(30, height, 55, -x);
       fill(204, 102, 0);
       rect(90, height, 55, -y);
       fill(204, 102, 100);
       rect(150, height, 55, -pot);
      
      fill(0,0,0);
      rect(0,0,249,60);
      fill(204, 102, 0);
      textSize(18);
      text("Temp (C):", 10, 30);
      text(t,100,30);
      text("Hum (%):", 10, 50);
      text(h,100,50);
      
      if (button==1){
        fill(0,0,0);
        rect(0,85,249,25);
        fill(204, 102, 0);
        textSize(18);
        text("Button pressed", 10, 105);
     
      } else 
      {
        fill(0,0,0);
        rect(0,85,249,25);
        fill(204, 102, 0);
        textSize(18);
        text("Button not pressed", 10, 105);
      }
      
     }
   }
 }
