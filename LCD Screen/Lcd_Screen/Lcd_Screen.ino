 #include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // sets the interfacing pins

void setup()
{
 lcd.begin(16, 2);  // initializes the 16x2 LCD
}

void loop()
{
  lcd.setCursor(1,0);           //sets the cursor at row 0 column 0
  lcd.print("16x2 LCD MODULE");   // prints 16x2 LCD MODULE
  delay(800);
  lcd.clear(); 
  delay(800);
  lcd.setCursor(2,1);           //sets the cursor at row 1 column 2
  lcd.print("HELLO WORLD");   // prints HELLO WORLD
  delay(800); 
  lcd.clear();
  delay(500); 
} 

                    
/*#include "LiquidCrystal.h"

// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
lcd.begin(16,2);

// set cursor position to start of first line on the LCD
lcd.setCursor(0,0);
//text to print
lcd.print("  LCD");
// set cusor position to start of next line
lcd.setCursor(0,1);
lcd.print("   WORKING");
}
void loop()
{} */
