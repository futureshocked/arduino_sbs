int potentiometerPin = 0;
int ledPin = 11;
int potentiometerVal = 0;

void setup()
{
  Serial.begin(9600);          //  setup serial
}

void loop()
{
  potentiometerVal = analogRead(potentiometerPin);
 
 //I use the map function because PWM pins can only accept
 //values from 0 to 255. Analog pins can output values from
 //0 to 1023. With the map function, the range 0-1023 is 
 //converted to appropriate values from 0 to 255.
 int mappedVal = map(potentiometerVal,0,1023,0,255);
 Serial.print(potentiometerVal);
 Serial.print(" - ");
 Serial.println(mappedVal);
 analogWrite(ledPin,mappedVal);
 delay(10); 
}
