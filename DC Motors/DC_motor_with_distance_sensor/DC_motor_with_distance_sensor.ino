//Arduino PWM Speed Control：
int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7;                        

#define trigPin 13
#define echoPin 12

void setup() 
{ 
    Serial.begin (9600);
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
} 

void loop() 
{ 
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  move_motors(distance); 
}

void move_motors(int distance)
{
  if (distance >= 50 ){
    Serial.print(distance);
    Serial.println(" cm - 255");
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 0);   //PWM Speed Control
    analogWrite(E2, 0);
    delay(30); 
  }
  else {
    int mappedVal = map(distance,0,50,0,255);
    Serial.print(distance);
    Serial.print(" cm - ");
    Serial.println(mappedVal);
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 255-mappedVal);   //PWM Speed Control
    analogWrite(E2, 255-mappedVal);   //PWM Speed Control
    delay(30); 
  }
}
