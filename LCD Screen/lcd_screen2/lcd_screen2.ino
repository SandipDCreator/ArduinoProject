#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int m=0;
void setup() 
{
    lcd.begin(16, 2);
}

void loop() 
{
 if(m == 0) 
 {
  lcd.setCursor(2, 0);
  lcd.print("10");
    delay(500);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("9");
    delay(500);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("8");
    delay(500);
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("7");
    delay(500);
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("6");
    delay(500);
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("5");
    delay(500);
  lcd.clear();
  lcd.setCursor(8,0);
  lcd.print("4");
    delay(500);
  lcd.clear();
  lcd.setCursor(9,1);
  lcd.print("3");
    delay(500);
  lcd.clear();
  lcd.setCursor(10,0);
  lcd.print("2");
    delay(500);
  lcd.clear();
  lcd.setCursor(11,1);
  lcd.print("1");
    delay(500);
  lcd.clear();
  lcd.setCursor(12,0);
  lcd.print("0");
    delay(500);
  lcd.clear();
 }
  m=1;
  lcd.setCursor(5,0);
  lcd.print("HAPPY");
  lcd.setCursor(3,1);
  lcd.print("NEW YEAR!!!");
  delay(1000);
  lcd.clear();
  delay(400);
} 
