
/* 
 *  ----------------------------------------------------------------------------- 
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               51                MOSI
 * SPI MISO   12               50                MISO
 * SPI SCK    13               52                SCK

  */

#include<SPI.h>
#include<MFRC522.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define RSTPIN 9
#define SSPIN 10
MFRC522 rc(SSPIN, RSTPIN);

int readsuccess=0;

byte defcard[][4]={{0xE5,0xA7,0xFA,0xC2}, {0xE0,0x0E,0x7E,0x1C}};      //for multiple cards  //2nd array last block should be 1B instead of 1C for actual Tag
int N=2;       //change this to the number of cards/tags you will use
byte readcard[4];       //stores the UID of current tag which is read

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


void setup() 
{

lcd.begin(16,2);    //Defining 16 columns and 2 rows of lcd display
lcd.backlight();

SPI.begin();
rc.PCD_Init();     //initialize the receiver  

}


void loop() 
{

 here: 
 lcd.setCursor(0,0);
 lcd.print("Scan Access Card");


 readsuccess = getId();
 if(readsuccess)
 { 
  lcd.clear();

   int match=0;

   match = isMatch();
  
   if(match) 
   {       
       for(int v=0; v<3; v++) 
       {
         lcd.clear();
         delay(200);
         lcd.setCursor(6,0);
         lcd.print("CARD");
         lcd.setCursor(2,1);
         lcd.print(" AUTHORISED!");
         delay(1000);
         lcd.clear();
       }
    }
      
    else 
    {
       for(int v=0; v<3; v++) 
       {
         lcd.clear();
         delay(200);
         lcd.setCursor(5,0);
         lcd.print("CARD");
         lcd.setCursor(0,1);
         lcd.print("NOT AUTHORISED!");
         delay(1000);
         lcd.clear();
       }
     }    
   }
}


int getId()         //function to get the UID of the card
{  
  
  int z=0;
  
  if(!rc.PICC_IsNewCardPresent())
    return 0; 
  if(!rc.PICC_ReadCardSerial())
    return 0;

  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Card UID:");
   
  for (byte i = 0; i < rc.uid.size; i++) 
  {
    readcard[i]=rc.uid.uidByte[i];
    lcd.setCursor(1+z,1);
    lcd.print(rc.uid.uidByte[i] < 0x10 ? " 0" : " ");
    lcd.print(rc.uid.uidByte[i], HEX);  
    z=z+3;
  } 
  delay(1500);
  lcd.clear();
  
  rc.PICC_HaltA();
  
  return 1;
}


int isMatch()         //Function to Compare the current tag with pre defined tags
{
  int ret = 0;
  for(int i=0; i<N; i++)
  {
    lcd.clear();
    lcd.print(" Matching with");
    delay(200);
    lcd.setCursor(2, 1);
    lcd.print(" Card ");
    lcd.setCursor(8, 1);
    lcd.print(i+1);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(800);
    
    if(!memcmp(readcard, defcard[i], 4)) 
      ret++;   
  }  
  return ret;
}


