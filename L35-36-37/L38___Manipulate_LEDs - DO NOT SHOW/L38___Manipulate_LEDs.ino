/*
 * WebServerParsing
 *
 * Respond to requests in the URL to change digital and analog output ports
 * show the number of ports changed and the value of the analog input pins.
 *
*/

#include <SPI.h>
#include <Ethernet.h>
#include <TextFinder.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,111,177 };
String message;
EthernetServer server(80);

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("ready");
}

void loop()
{
  EthernetClient client = server.available();
  
  message = "";
  
  if (client) {
    TextFinder  finder(client );
    while (client.connected()) {
      if (client.available()) {
        if( finder.find("GET /") ) {
          // find tokens starting with "pin" and stop on the first blank line
          while(finder.findUntil("pinD", "\n\r")){
            int pin = finder.getValue();
            int val = finder.getValue();
            Serial.print("Digital pin ");
            pinMode(pin, OUTPUT);
            digitalWrite(pin, val);
            Serial.print(pin);
            Serial.print("=");
            Serial.println(val);
            message += "Pin";
            message += pin;
            message += "=";
            message += val;
            message += ". ";
            }         
        }
        Serial.println();

        // OK, now send a standard http response header
        print_header(client);

        // output the number of pins handled by the request
        print_confirmation(message, client);
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}

void print_header(EthernetClient &client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
}
      
void print_confirmation(String &confirmation_message, EthernetClient &client)
{
  client.print("Action(s) performed:<b>");
  client.print(confirmation_message);
  client.print("</b>");
}
    

