#include "LiquidCrystal.h"

LiquidCrystal lcd(12,11,5,4,3,2);

char tag[] ="1C002492359F"; 
char input[12];        
int count = 0;       
boolean flag = 0;    
int led=9;
int led2=8;
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);   
}
void loop()
{
  if(Serial.available())
  {
    count = 0; 
    while(Serial.available() && count < 12) 
    {
      input[count] = Serial.read(); 
      count++; 
      delay(5);
    }
    if(count == 12)  
    {
      count =0;
      flag = 1;
      while(count<12)  
      {
        if(input[count]==tag[count])
         flag = 1; 
        else
         flag= 0;                                   
        count++; 
      }
    }
    if(flag == 1)
    {
      Serial.println("Access Allowed!");
      lcd.setCursor(0,0);           
      lcd.print("ATTENDANCE"); 
      lcd.setCursor(2,1);           
      lcd.print("RECORDED"); 
      delay(3000);
      lcd.clear();
    }
    else
    {
      Serial.println("Access Denied"); 
      lcd.setCursor(0,0);           
      lcd.print("ATTENDANCE"); 
      lcd.setCursor(2,1);           
      lcd.print("NOT RECORDED"); 
      delay(3000);
      lcd.clear();
    }
    for(count=0; count<12; count++) 
      input[count]= 'F';
    count = 0;
  }
}
