/*
 Chat  Server
 
 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to  your device's IP address and type.
 You can see the client's input in the serial monitor as well.
 Using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
This sketch reports on the value read by a photoresistor connected to 
Analog pin 0, and turns an LED connected to digita pin 2 on and off.
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,111, 177);
IPAddress gateway(192,168,111, 1);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(23);
boolean alreadyConnected = false; // whether or not the client was connected previously

int ledPin = 2; 

String commandString;

void setup() {
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);
  // start listening for clients
  server.begin();
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // wait for a new client:
  EthernetClient client = server.available();
  commandString = "";

  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();    

      server.println("--> Please type your command and hit Return...");
      alreadyConnected = true;
    } 

    while (client.available()) {
      server.println("--> Please type your command and hit Return...");
      
      // read the bytes incoming from the client:
      char newChar = client.read();
     

     if (newChar == 0x0D)  //If a 0x0D is received, a Carriage Return, then evaluate the command
     {
         server.print("Received this command: ");
         server.println(commandString);   
         processCommand(commandString);
     } else
     {
       Serial.println(newChar);
         commandString += newChar;
     }

    }
  }
}

void processCommand(String command)
{
  server.print("Processing command ");
  server.println(command);
  
  if (command.indexOf("photo") > -1){
    Serial.println("Photo command received"); 
    server.print("Reading from photoresistor: " );
    server.println(analogRead(0));     //Print the integer returned by analogRead to the server object
    commandString = "";
    return;
  } 
  
  if (command.indexOf("ledon") > -1){
    server.println("LED On command received"); 
    digitalWrite(ledPin, HIGH);   // sets the LED on
    server.println("LED was turned on");
    commandString = "";
    return;
  } 
  
  if (command.indexOf("ledoff") > -1){
    Serial.println("LED Off command received"); 
    digitalWrite(ledPin, LOW);   // sets the LED off
    server.println("LED was turned off");
    commandString = "";
    return;
  } 
    
//   String commandString;
   commandString = "";
   server.println("I don't understand");
   server.println("Please use one of these commands:");
   server.println("* photo, to get a reading from the photoresistor");
   server.println("* ledon, to turn on the LED");
   server.println("* ledoff, to turn off the LED");

}


