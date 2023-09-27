int red = 13;
int yellow = 11;
int blue = 8;
int brightness = 0;    
int fadeAmount = 5;
int i=0;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  digitalWrite(red, HIGH);   
  delay(400);                     
  digitalWrite(red, LOW);   
  delay(400);  
  for(; i<2 ; )
  {
   analogWrite(yellow, brightness);
   brightness = brightness + fadeAmount;
   if (brightness == 0 || brightness == 255)
   {
     fadeAmount = -fadeAmount ;
     i++;
   }
   delay(40);
  }   
  i=0;
  delay(100);              
  digitalWrite(yellow, LOW);
  delay(400); 
  digitalWrite(blue, HIGH);
  delay(400); 
  digitalWrite(blue, LOW);
  delay(400); 
}
