#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void setup() 
{
lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the back light
//lcd.backlight();// To Power OFF the back light
}

void loop() 
{
lcd.setCursor(5,0);
delay(800);
lcd.print("Hello");
delay(500);
lcd.setCursor(5,1);
lcd.print("World");
delay(1000); 
lcd.clear();
delay(500);
}


