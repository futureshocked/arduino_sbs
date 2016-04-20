/*
 * A simple web server with a GET request parser.
 *
*/

#include <SPI.h>
#include <Ethernet.h>

byte           mac[]        = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte           ip[]         = { 192,168,111,177 };
String         message      = "";     //Will hold the confirmation message that will be shown to the user
EthernetServer server(80);
String         get_request  = "";     //Holds the GET request
boolean        reading      = false;  //TRUE while the GET request is being received

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("ready");
}

void loop() {
  // listen for incoming clients
  EthernetClient   client = server.available();
  String return_message; 
  if (client) {
    Serial.println("new client");
    boolean sentContent    = false;
    get_request           = "";
    
    while (client.connected()) {
      if (client.available()) {
        char       c = client.read();
        //A raw GET request looks like this:
        //GET /path/to/file/index.html?a=1 HTTP/1.0
        //Notice the space between the "1" in "a=1" and the "H" in "HTTP"?
        //Once we detect this space, we know that we have completed reading the 
        //querry string, and the rest of the request is not important,
        //therefore we can stop reading.
        //This happens in the following block
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
      }
    }
    
    if (!sentContent){
       construct_page(client, return_message);         
       sentContent = true;        
     }
    
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void construct_page(EthernetClient client, String rmessage)
{
    print_header(client);
    print_form(client);
    print_confirmation(rmessage, client);
    end_page(client);
}

void print_header(EthernetClient &client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print("<html><head><title>");   
    client.print("GET request example");
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
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led8'");
  client.println(" value='0'><input type='submit' value='Off'/></form>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led8'");
  client.print(" value='1'><input type='submit' value='On'/></form>");
}
    
void end_page(EthernetClient &client)
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

