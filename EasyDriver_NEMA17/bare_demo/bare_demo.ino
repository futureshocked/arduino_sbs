void setup() {                
  pinMode(8, OUTPUT);     
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void loop() {
  digitalWrite(8, LOW);  
  for (int i=0;i<800;i++)
  {
  
  digitalWrite(9, HIGH);
  delay(1);          
  digitalWrite(9, LOW); 
  delay(1); 
  }
  digitalWrite(8, HIGH);  
  
  for (int i=0;i<800;i++)
  {
    digitalWrite(9, HIGH);
    delay(1);          
    digitalWrite(9, LOW); 
    delay(1); 
  }
}
