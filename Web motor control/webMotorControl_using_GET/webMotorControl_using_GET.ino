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
String         get_request;     //Holds the GET request
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
char           return_message[30]; 
  if (client) {
    Serial.println("new client");
    boolean sentContent    = false;
    get_request           = "";

    boolean        currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char       c = client.read();
        if(reading && c == ' ') 
        { reading = false;  
          parseGetRequest(get_request);
          
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
       construct_page(client);//, return_message);         
       sentContent = true;        
     }
    
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void construct_page(EthernetClient &client)
{
    print_header(client);
    print_form(client);
    print_confirmation(client);
    end_page(client);
}

void print_header(EthernetClient &client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print("<html><head><title>");   
    client.print("GET motor control example");
    client.println("</title><body>");
}
      
void print_confirmation(EthernetClient &client)
{
  client.print("Action performed: <b>");
  client.print(get_request);
  client.print("</b>");
}

void print_form(EthernetClient &client)
{
  client.print("<form action='/' method='GET'>");
  client.print("<h1>Forward Speed</h1>");
  client.print("<input type='radio' name='speed5' value='0' onclick='this.form.submit()'>Stopped</input>");
  client.print("<input type='radio' name='speed5' value='63' onclick='this.form.submit()'>1/4</input>");
  client.print("<input type='radio' name='speed5' value='127' onclick='this.form.submit()'>1/2</input>");
  client.print("<input type='radio' name='speed5' value='184' onclick='this.form.submit()'>3/4</input>");
  client.print("<input type='radio' name='speed5' value='254' onclick='this.form.submit()'>FULL!</input>");
  client.print("<input type='hidden' name='direction4' value='0'>");
  client.print("</form>");
  
  client.print("</br>");
  client.print("<form action='/' method='GET'>");
  client.print("<h1>Backward Speed</h1>");
  client.print("<input type='radio' name='speed5' value='254' onclick='this.form.submit()'>Stopped</input>");
  client.print("<input type='radio' name='speed5' value='184' onclick='this.form.submit()'>1/4</input>");
  client.print("<input type='radio' name='speed5' value='127' onclick='this.form.submit()'>1/2</input>");
  client.print("<input type='radio' name='speed5' value='63' onclick='this.form.submit()'>3/4</input>");
  client.print("<input type='radio' name='speed5' value='0' onclick='this.form.submit()'>FULL!</input>");
  client.print("<input type='hidden' name='direction4' value='1'>");
  client.print("</form>");
}
    
void end_page(EthernetClient &client)
{     
    client.print("</body>");
    client.print("</html>");
}

void parseGetRequest(String &str) {
  //We need to parse something like this: "?speed1=50&direction1=0"
  Serial.print(" Parsing this string:");
  Serial.println(str);
  //We need to get the speed and the direction. Speed will have a value made of 1 or 2 digits.
  
  //Notice the value-pair delimiter character: "&"
  int delimiter_index = str.indexOf("&");
  Serial.print("delimiter_index: ");
  Serial.println(str.indexOf("&"));
  
  //Get the speed
  int   speed_index  = str.indexOf("speed");
  Serial.print("motor_number: ");
  Serial.println(str[speed_index + 5]);  
  int   motor_number = str[speed_index + 5] - '0';
  
  //Here's, I am trying to avoid using the substring function because I have been
  //having problems with it and it seems unstable.
  //Instead, I just just an array of chars and copying the speed value from the
  //str variable into the array of chars.
  char speed_value_array[4];
  for(int i = speed_index + 7; i < delimiter_index; i++){
    Serial.print(i-8);
    Serial.print("-");
     speed_value_array[i - 8] = str[i];
     Serial.print(str[i]);
         Serial.print("+");
  }
  Serial.println();
  int   motor_speed_value = atoi(speed_value_array);
  Serial.print("Motor speed value: ");
  Serial.println(motor_speed_value);
  
  //Get the direction
  int   direction_number    = str[delimiter_index + 10] - '0';
  Serial.print("direction_number: ");
  Serial.println(str[delimiter_index + 10]);
  int   direction_value = str[delimiter_index + 12] - '0';
  Serial.print("direction_value: ");
  Serial.println(str[delimiter_index + 12]);
 
  executeInstruction(motor_number, motor_speed_value, direction_number, direction_value);
}

void executeInstruction(int motor_number, int motor_speed_value, int dir_pin, int direction_value)
{   
    pinMode(dir_pin, OUTPUT);   
    pinMode(motor_number, OUTPUT); 
    digitalWrite(dir_pin,direction_value);   
    analogWrite(motor_number, motor_speed_value);   //PWM Speed Control
    delay(30); 
}

