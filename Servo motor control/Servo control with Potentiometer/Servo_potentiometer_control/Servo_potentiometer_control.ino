#include<Servo.h>
 
Servo servo;
int i=0;

void setup() { 

 servo.attach(7);
 
}

void loop() 
{
 int val=analogRead(0);
 val=map(val, 0, 1023, 0, 180);
 servo.write(val);
 delay(100);
}
