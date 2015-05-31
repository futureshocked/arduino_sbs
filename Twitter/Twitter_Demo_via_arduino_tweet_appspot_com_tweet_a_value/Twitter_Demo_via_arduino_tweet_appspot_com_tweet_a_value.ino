#include <SPI.h> // needed in Arduino 0019 or later
#include <Ethernet.h>
#include <Twitter.h>
#include <PString.h>     

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10000;

// Ethernet Shield Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// If you don't specify the IP address, DHCP is used(only in Arduino 1.0 or later).
byte ip[] = { 192, 168, 111, 167 };

// Your Token to Tweet (get it from http://asbs-tweet.appspot.com/)
Twitter twitter("---Enter your token here---");

// Message to post
char tweet[200];
PString tweet_pstring(tweet, sizeof(tweet));

void setup()
{
  Ethernet.begin(mac, ip);
  // or you can use DHCP for autoomatic IP address configuration.
  // Ethernet.begin(mac);
  Serial.begin(9600);
}

void loop()
{
    if((millis() - lastConnectionTime > postingInterval)) {
        tweet_pstring.begin();
        int ana_A = analogRead(0);
        Serial.println("connecting ...");
        tweet_pstring.print("Light intensity:");
        tweet_pstring.print(ana_A);
        if (twitter.post(tweet_pstring)) {
            // Specify &Serial to output received response to Serial.
            // If no output is required, you can just omit the argument, e.g.
            //int status = twitter.wait();
            int status = twitter.wait(&Serial);
            if (status == 200) {
               Serial.println("OK.");
            } else {
               Serial.print("failed : code ");
               Serial.println(status);
            }
          } else {
            Serial.println("connection failed.");
         }
         // note the time that the connection was made
         lastConnectionTime = millis();
      }
}
