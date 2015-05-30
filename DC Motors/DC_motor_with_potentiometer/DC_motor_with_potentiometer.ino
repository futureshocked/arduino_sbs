//Arduino PWM Speed Control：
int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7;                        

void setup() 
{ 
    Serial.begin (9600);
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
} 

void loop() 
{ 
  int potentiometerVal = analogRead(A0);
  Serial.println(potentiometerVal);
  move_motors(potentiometerVal);
}

void move_motors(int potValue)
{
  if (potValue < 512)
   {
     int mappedVal = map(potValue,0,512,0,255);
     //Going forward
      digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, mappedVal);   //PWM Speed Control
    analogWrite(E2, mappedVal);   //PWM Speed Control
    delay(30); 
   } else
   {
     //Going backward
        int mappedVal = map(potValue-512,0,512,0,255);
    digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, mappedVal);   //PWM Speed Control
    analogWrite(E2, mappedVal);   //PWM Speed Control
    delay(30); 
   }
}
