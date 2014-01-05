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
char buffer[8]; // buffer holding the requested page name

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
        if(finder.getString("","/", buffer,sizeof(buffer))){ 
          if(strcmp(buffer,"POST ") == 0){
            finder.find("\n\r"); // skip to the body
            // find string starting with "pin", stop on first blank line
            // the POST parameters expected in the form pinDx=Y
            // where x is the pin number and Y is 0 for LOW and 1 for HIGH
           
          if(finder.findUntil("pinD", "\n\r")){
              int pin = finder.getValue();       // the pin number
              int val = finder.getValue();       // 0 or 1
              pinMode(pin, OUTPUT);
              digitalWrite(pin, val);
              message += "Pin ";
              message += pin;
              message += " set to ";
              message += val;
            }
          }
        }
        // OK, now send a standard http response header
        print_header(client);
        //Print the buttons
        print_form(client);
        // output the number of pins handled by the request
        print_confirmation(message, client);
        end_page(client);
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
    client.print("<html><head><title>");   
    client.print("POST example");
    client.println("</title><body>");
}
      
void print_confirmation(String &confirmation_message, EthernetClient &client)
{
  client.print("Action(s) performed: <b>");
  client.print(confirmation_message);
  client.print("</b>");
}

void print_form(EthernetClient &client)
{
  client.println("<h2>Click buttons to turn pin 8 on or off</h2>");
  client.print("<form action='/' method='POST'><p><input type='hidden' name='pinD8'");
  client.println(" value='0'><input type='submit' value='Off'/></form>");

          //create HTML button to turn on pin 
  client.print("<form action='/' method='POST'><p><input type='hidden' name='pinD8'");
  client.print(" value='1'><input type='submit' value='On'/></form>");
}
    
void end_page(EthernetClient &client)
{     
    client.print("</body>");
    client.print("</html>");
}

