/*************************************************** 
  This is an example for the Adafruit CC3000 Wifi Breakout & Shield

  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
  Modified by Peter Dalmaris to enable periodic polling of a URL.
 ****************************************************/
 
 /*
This example does a test of the TCP client capability:
  * Initialization
  * Optional: SSID scan
  * AP connection
  * DHCP printout
  * DNS lookup
  * Optional: Ping
  * Connect to website and print out webpage contents
  * Disconnect
SmartConfig is still beta and kind of works but is not fully vetted!
It might not work on all networks!
*/
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <avr/wdt.h>

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

boolean        reading      = false;  //TRUE while the GET request is being received
String         get_request  = "";     //Holds the GET request

#define WLAN_SSID       "yourssid"           // cannot be longer than 32 characters!
#define WLAN_PASS       "yourpassword"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

// What page to grab!
#define WEBSITE      "arduinosbs.com.s3.amazonaws.com"
#define WEBPAGE      "/cc3000.txt"


/**************************************************************************/
/*!
    @brief  Sets up the HW and the CC3000 module (called automatically
            on startup)
*/
/**************************************************************************/

uint32_t ip;
uint32_t   t;
int port = 80;
int connectTimeout  = 5000; // Max time to wait for server connection
Adafruit_CC3000_Client www;

int repeat_counter = 0;

void setup(void)
{
  Serial.begin(115200);
  Serial.println(F("Hello, CC3000!\n")); 

  Serial.print(F("Free RAM: ")); Serial.println(getFreeRam(), DEC);
}

void loop(void)
{ 
  repeat_counter++;
  
  Serial.print(F("Free RAM: ")); Serial.println(getFreeRam(), DEC);
  Serial.print(F("Repeat counter: ")); Serial.println(repeat_counter);
  initWifi();
  deleteOldConn();
  connect_wifi();
  get_dhcp();
  lookup_ip();
  Serial.print(F("starting connection to "));
  Serial.println(ip);
  wdt_enable(WDTO_8S);
   connect_tcp();
  wdt_disable();
  Serial.println(F("Connecting"));

  if (www.connected()) {
    Serial.println(F("Connected"));
    make_get_request();

    Serial.println(F("Request sent"));
  } else {
    Serial.println(F("Connection failed"));    
    return;
  }

  Serial.println(F("-------------------------------------"));
  
  /* Read data until either the connection is closed, or the idle timeout is reached. */ 
  unsigned long lastRead = millis();
  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    boolean currentLineIsBlank = true;
    get_request           = "";     
    boolean sentContent    = false;
    while (www.available()) {   
       char c = www.read();
       Serial.print(c);

       if(reading && c == '\n') 
        { reading = false;  
          parseGetRequest(get_request);
          break;
        }        

        if(reading){ 
            get_request += c;
         }      
       if (reading && c=='\n')
       {
        break; 
       }       
       if (c == '\n' && currentLineIsBlank)  {
        reading = true; // Found the body of the server response, start reading
       }
       if (c == '\n') {
          currentLineIsBlank = true;
       } 
       else if (c != '\r') {
          currentLineIsBlank = false;
       }
    }
  }
  www.close();
  Serial.println(F("-------------------------------------"));
  cc3000.disconnect();
   delay(10000);
}

void parseGetRequest(String &str) {
  Serial.print(F("Parsing this string:"));
  Serial.println(str);
  int   led_index  = str.indexOf("led");
  int   led_pin    = str[led_index + 3] - '0';
  int   led_val    = str[led_index + 5]  - '0';
  executeInstruction(led_pin, led_val);
}

void executeInstruction(int pin, int val)
{   Serial.println(F("Executing instruction"));
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    Serial.println(F("Done!"));
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

void make_get_request(){
    www.fastrprint(F("GET "));
    www.fastrprint(WEBPAGE);
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: ")); www.fastrprint(WEBSITE); www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println();
  }

void connect_tcp(){
  t = millis();
    do {
    www = cc3000.connectTCP(ip, port);
  }   
  while((!www.connected()) &&
    ((millis() - t) < connectTimeout));
}

void connect_wifi()
{
 if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("Connected!"));
 
}

void get_dhcp()
{
  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }
}

void lookup_ip()
{
  ip = 0;
  // Try looking up the website's IP address
  Serial.print(WEBSITE); Serial.print(F(" -> "));
  while (ip == 0) {
    if (! cc3000.getHostByName(WEBSITE, &ip)) {
      Serial.println(F("Couldn't resolve!"));
    }
    delay(500);
  }
  cc3000.printIPdotsRev(ip); 
}

void initWifi(){
  Serial.println(F("\nInitialising the CC3000 ..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while(1);
  }
}

void deleteOldConn(){
  /* Delete any old connection data on the module */
  Serial.println(F("\nDeleting old connection profiles"));
  if (!cc3000.deleteProfiles()) {
    Serial.println(F("Failed!"));
    while(1);
  }
}
