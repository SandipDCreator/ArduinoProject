/*
 Fade
 
 This example shows how to fade an LED on pin 3
 using the analogWrite() function.
 
 This example code is in the public domain.
 */
 
int led = 3;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 10;    // how many points to fade the LED by
 
// the setup routine runs once when you press reset:
void setup() {
  // declare pin 3 to be an output:
  pinMode(led, OUTPUT);
}
 
// the loop routine runs over and over again forever:
void loop() 
{  
  // set the brightness of pin 3:
  analogWrite(led, brightness);
 
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
 
  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 200) {
    fadeAmount = -fadeAmount ;   
  }
  // wait for 100 milliseconds to see the dimming effect
  delay(100);
    
}
