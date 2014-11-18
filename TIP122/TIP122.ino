const int led_pin = 13;
long randOn = 0;
long randOff = 0;

void setup()
{
   randomSeed(analogRead(0));
   pinMode(led_pin,OUTPUT); 
}

void loop()
{
   randOn = random(50,500); 
   randOff = random(50,500);
   digitalWrite(led_pin,HIGH);
   delay(randOn);
   digitalWrite(led_pin,LOW  );
   delay(randOff);
}
