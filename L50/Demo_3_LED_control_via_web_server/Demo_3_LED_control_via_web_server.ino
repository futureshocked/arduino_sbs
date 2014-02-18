// Include required libraries
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <stdlib.h>

String result;

// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// WiFi network (change with your settings !)
#define WLAN_SSID       "yourssid"           // cannot be longer than 32 characters!
#define WLAN_PASS       "yourpassword"

#define WLAN_SECURITY   WLAN_SEC_WPA2 // This can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

// What TCP port to listen on for connections.
#define LISTEN_PORT           80   

// Create CC3000 instances
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2);                                
                                         
// Create server
Adafruit_CC3000_Server ledServer(LISTEN_PORT);

String         get_request  = "";     //Holds the GET request
boolean        reading      = false;  //TRUE while the GET request is being received

void setup() {
   
  Serial.begin(115200);
    
  /* Initialise the module */
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("Connected!"));
  
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }
 
  // Start listening for connections
  ledServer.begin();
  
  Serial.println(F("Listening for connections..."));
 
}

void loop() {
  
  // Try to get a client which is connected.
  Adafruit_CC3000_ClientRef client = ledServer.available();
    String return_message; 
  if (client) {
     boolean currentLineIsBlank = true;
         get_request           = "";
     // Check if there is data available to read.
         boolean sentContent    = false;
     while (client.available()) {   
       char c = client.read();
//       Serial.print(c);
       if(reading && c == ' ') 
        { reading = false;  
          return_message = parseGetRequest(get_request);
          break;
        }
        
        if(c == '?'){
          reading = true; //found the ?, begin reading the info
        }

        if(reading){ 
            get_request += c;
         }

      
       if (reading && c=='\n')
       {
        break; 
       }
       
        if (c == '\n' && currentLineIsBlank)  {
         break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
           
     }
     if (!sentContent){
       construct_page(client, return_message);         
       sentContent = true;        
     }
     // give the web browser time to receive the data
    delay(5);
    // close the connection:
    client.close();
    Serial.println("client disconnected");
    
    result = "";
  }
           
}

void construct_page(Adafruit_CC3000_ClientRef &client, String &rmessage)
{
    print_header(client);
    print_form(client);
    print_confirmation(rmessage, client);
    end_page(client);
}

void print_header(Adafruit_CC3000_ClientRef &client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print("<html><head><title>");   
    client.print("GET request example");
    client.println("</title><body>");
}
      
void print_confirmation(String &confirmation_message, Adafruit_CC3000_ClientRef &client)
{
  client.print("Action(s) performed: <b>");
  client.print(confirmation_message);
  client.print("</b>");
}

void print_form(Adafruit_CC3000_ClientRef &client)
{
  client.println("<h2>Click buttons to turn pin 8 on or off</h2>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led8'");
  client.println(" value='0'><input type='submit' value='Off'/></form>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led8'");
  client.print(" value='1'><input type='submit' value='On'/></form>");
}
    
void end_page(Adafruit_CC3000_ClientRef &client)
{     
    client.print("</body>");
    client.print("</html>");
}

String parseGetRequest(String &str) {
  Serial.print(" Parsing this string:");
  Serial.println(str);
  int   led_index  = str.indexOf("led");
  int   led_pin    = str[led_index + 3] - '0';
  int   led_val    = str[led_index + 5]  - '0';
  String return_message = "";
  return_message = "Setting LED ";
  return_message += led_pin;
  return_message += " to ";
  return_message += led_val;
  executeInstruction(led_pin, led_val);
  return return_message;
}

void executeInstruction(int pin, int val)
{  
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
}

/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}

