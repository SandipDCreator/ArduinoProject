#include<Servo.h>
#include<LiquidCrystal.h>

Servo servo;
int i=0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() { 

 lcd.begin(16, 2);
 servo.attach(7);
 
}

void loop() 
{

 lcd.setCursor(3, 0);
 lcd.print("Servo Motor");
 lcd.setCursor(1, 1);
 lcd.print("Function Begins");
 delay(5000);
 lcd.clear();
 for(i=0 ; i<180 ; i++)
 {
  lcd.setCursor(5, 0);
  lcd.print("Angle: ");
  lcd.setCursor(6, 1);
  lcd.print(i);
  servo.write(i);
  delay(100);
  lcd.clear();
 } 
 lcd.setCursor(5, 0);
 lcd.print("Angle: ");
 lcd.setCursor(6, 1);
 lcd.print(i);
 delay(3000);
 lcd.clear();
 for(i=180; i>0; i--)
 {
  lcd.setCursor(5, 0);
  lcd.print("Angle: ");
  lcd.setCursor(6, 1);
  lcd.print(i);
  servo.write(i);
  delay(100);
  lcd.clear();
 }
}
