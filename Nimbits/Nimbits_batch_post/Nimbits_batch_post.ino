
/*
current on October-03-2012. StewieT.

batch posts to nimbits
Uses the PString.h library.
Instead of making many connections to the server using the usual Arduino ethernet functions
like 'client.print' (every statement is a separate set of ethernet transactions), all the data to send in the 
POST trasaction is 'assembled' into one string using the Pstring library, which then gets sent in one hit.
This reduces the IP traffic considerably and when faultfinding with a packet sniffer, its easier
to see what you are looking for

Updated by Peter Dalmaris, June 21, 2015
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PString.h>            // from http://arduiniana.org/libraries/pstring/
                                // allows 'printing' to a string buffer

char buffer[400];            // larger than required for this example, resize to suit your application
char content[200];           // larger than required for this example, resize to suit your application
PString str(buffer, sizeof(buffer));
PString cont(content, sizeof(content));

int rand_A ;    // variables to store random values

/************ ETHERNET STUFF ************/
byte mac[] = { 
    0xDE, 0xAD, 0x45, 0xEF, 0xFE, 0xED };

// adjust these to suit your local setup. 
byte ip[] = {192,168,111,177 };                // ethernet cards address
byte nameserver[] = {192,168,111,1 };
byte gateway[] = {192,168,111,1 };
byte subnet[] = {255,255,255,0 };

EthernetClient nimbitsServiceClient;
//***************************************

unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10000;  // 10-sec delay between updates to logging service, 720 per 24hrs to keep within the 1000 quota
                                              // and leave room for other types of API access. 
                                              // Should really reduce this to one post every 10-20 minutes 

// these are for your nimbits account
char mailaddr [] = "your@email.com";    // your email address for the logging account
char key [] = "your_access_token";                     // your KEY you created for the account. Not the UUID.
char datapoint [] = "your_datapoint";


void setup() {
    Serial.begin(9600);    // serial debug
    Ethernet.begin(mac, ip, nameserver, gateway, subnet);
    Serial.println("up and running....");
    Serial.print("POST interval is ");
    Serial.print(postingInterval/1000);
    Serial.println(" seconds");
}

void loop()
{
    rand_A = random(10,110);    // create a random decimal
    do_weblog();
} 

// =========================================================================
/*
This is where it all happens.
If the posting interval is reached then a new POST is done with the latest data
If not time yet, we simply exit
 */
void do_weblog() {
    // if you're not connected, and 'postinginterval' secs have passed since
    // your last connection, then connect again and send data:
    if(!nimbitsServiceClient.connected() && (millis() - lastConnectionTime > postingInterval)) {
        str.begin();    // reset the into-string pointer. This is the 'final' composite string being assembled.
        cont.begin();   // and for the actual content ie payload string
        sendData();    // the POST gets created and sent here
        delay(1);
        nimbitsServiceClient.stop();    // stop the client
        nimbitsServiceClient.flush();   // and tidy up
    }
}

void sendData() {
    // Get the data and store it in the 'cont' string
    // The data is saved into a JSON structure, using "d" for decimal and "dx" for a description.
    // These variables are expected by Nimbits.
    cont.print("json={\"d\"=");                 // d is the decimal value for this data point
    cont.print(ana_A,DEC);            
    cont.print(",\"dx\"=\"A random value\"}");  // dx is string that describes the decimal datapoint.
                                                // You may include other data inside dx.

    // now get the length of the assembled content string that will posted in the body of the request.
    int contlen = (cont.length());
      
    // now try and connect to the web-site
    Serial.println("connecting...");
    if (nimbitsServiceClient.connect("cloud.nimbits.com", 80))     // make the attempt...
    { 
        // the format of the POST section below seems to be fairly critical. 
        str.print("POST /service/v2/value?email=");       
        str.print(mailaddr);
        str.print("&id=");
        str.print(datapoint);
        str.print("&token=");
        str.print(key);
        str.print(" HTTP/1.1\r\n");
        str.print("Host: cloud.nimbits.com\r\n");
        str.print("Connection: close\r\n");
        str.print("Cache-Control: max-age=0\r\n");
        str.print("Content-Length: ");
        str.print(contlen,DEC);
        str.print("\r\n");
        str.print("Content-Type: application/x-www-form-urlencoded\r\n");
        str.print("\r\n");  // this empty line is REQUIRED
        str.print(cont);    // the actual content string 'cont' (access details, data points)
        str.print("\r\n");  // and a terminating newline
        // this completes the assembly of the string to send (contained in 'str')

        // the total string (post headers and content) is now sent to the ethernet connection in one hit
        nimbitsServiceClient.print(str);  // ethernet send to Nimbits

        Serial.println();        // for debug
        
        Serial.print(str);       // this is a copy of whats sent to the ethernet (the same string)
                                 // you can comment-out the line: nameofclient.print(str) above to just see the debug output
                                 // while testing. This lets you see if your POST looks sensible.
        
        Serial.println();        // for debug
        Serial.println();        // for debug

// shows the response from the server. Comment below if not required.
        delay(1500);        // wait 1.5 sec for a response
        while (nimbitsServiceClient.available()) {
          char c = nimbitsServiceClient.read();
          Serial.print(c);
        }
    }

    else {
        // if you couldn't make a connection:
        Serial.println();
        Serial.println("Connection failed");
        Serial.println("disconnecting.");
        Serial.println();
    }
    // note the time that the connection was made
    lastConnectionTime = millis();
}


