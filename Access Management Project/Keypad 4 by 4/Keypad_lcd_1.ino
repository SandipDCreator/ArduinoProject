// 4*4 Keypad displayed on LCD screen

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};        // Connection to Arduino Pins
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypress = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

int i=0, j=0, m=0;

void setup()
{
  lcd.begin(16, 2);
  lcd.backlight();
}

void loop()
{
  char key = keypress.getKey();

  if (key == NO_KEY && m == 0)
  {
    lcd.setCursor(1, 0);
    lcd.print("Press any Key");
    lcd.setCursor(1, 1);
    lcd.print("(# to Delete)");  
    delay(100);
    lcd.clear();
  }
  if (key)            // If Key is pressed
  {
     m=1;
     if(j > 1)            // If 2nd row is full, Clear screen and start from Row 1
     {
      lcd.clear();
      j=0;
     }
     if(key == '#')          // '#' Key as Backspace function
     {
      i--;

      if(i == -1)
      { 
        i=0;
        if(j == 1)
          i=15;  
        j=0; 
      }
      lcd.setCursor(i, j);
      lcd.print(" ");
      goto a;
    //  continue;
     }
     lcd.setCursor(i, j);
     lcd.print(key);          // Print pressed key on LCD
     i++;
     a: if(i > 15)              // If Column exceeds limit, go to next Row
     {
     i=0;
     j++;
     }
/*    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print(key);  */
  }
}
