#include<Servo.h>
 
Servo servo;
int i=0;

void setup() { 

 servo.attach(7);
 
}

void loop() 
{

 for(i=0 ; i<180 ; i++)
 {
  servo.write(i);
  delay(10);
 } 
 for(i=180; i>0; i--)
 {
  servo.write(i);
  delay(10);
 }
}
