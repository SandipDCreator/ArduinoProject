#include<SPI.h>
#include<MFRC522.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Keypad.h>



#define RSTPIN 14      //RFID MFRC522 pin connections.
#define SSPIN 10
MFRC522 rc(SSPIN, RSTPIN);
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

byte defcard[][4]={{0xE5,0xA7,0xFA,0xC2}, {0xE0,0x0E,0x7E,0x1B}};    //Multiple cards.
int N=2;      //Number of cards to be used.
byte readcard[4];   

byte blockNumber = 2;    //Block number to be read.
byte buffer1[18];      //Array for reading a block. MIFARE_Read method requires at least 18 bytes to hold 16 bytes of a block.
String value = "";    //String stores the Data in the card as human readable characters.


LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 



const byte ROWS = 4;     //Keypad Data
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};     //Connection to Arduino Pins.
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypress = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



int i=0, match=0;   //Variables for Password part.
const char password[9]={'1', '7', '9', '4', 'A', 'B', 'C', 'D'};    //Password for comparison.
char passcheck[9];
int passlen=8;     //Length of Password.


//********************************************************************************************************************


void setup() 
{
  Serial.begin(9600);
  lcd.begin(16,2);     
  lcd.backlight();

  SPI.begin();
  rc.PCD_Init();      //Initialize the RFID receiver.  

 // Serial.println(F("Read data on a MIFARE PICC:"));
  
  for (byte q = 0; q < 6; q++) 
     key.keyByte[q] = 0xFF;      
}


//********************************************************************************************************************


void loop() 
{

  back:            //RFID part Begins.----------------------------------------------
  while(!getId())         //getId() is user defined function.
  {
    lcd.setCursor(0,0);
    lcd.print("Scan Access Card");
  }

   match=0;

   match = isMatch();    //isMatch() is user defined function.
  
   if(match == 1) 
   {       
      lcd.setCursor(5,0);
      lcd.print("CARD");
      lcd.setCursor(2,1);
      lcd.print("AUTHORISED!");
      delay(2000);
      lcd.clear();
      delay(200);

      lcd.setCursor(4,0);       //Welcome message.
      lcd.print("Welcome");
      delay(400);  

      if(value[0] == 0)
      {
        lcd.setCursor(3,1);             
        lcd.print("New  User");
      }
      else
      {  
        for (int j=0 ; j<16 ; j++)   //Print the Data block contents.
        {
          lcd.setCursor(j+4, 1);       
          lcd.print(value[j]);     
        } 
      }      
      
      delay(2500); 
      lcd.clear(); 
      goto here;
    }
      
    else 
    {
       for(int v=0; v<2; v++) 
       {
         lcd.setCursor(5,0);
         lcd.print("CARD");
         lcd.setCursor(0,1);
         lcd.print("NOT AUTHORISED!");
         delay(1000);
         lcd.clear();
         delay(500);
       }
       goto back;
     }     




 here:               //Password part Begins.------------------------------------------
 while(i<(passlen+1))
 {
  if(i == 0)
  {
   lcd.setCursor(0, 0);
   lcd.print("Enter Password:");
   lcd.setCursor(0, 1);
   lcd.print("(#)-DEL ");
   lcd.setCursor(8, 1);
   lcd.print("(*)-SEND");  
  }
  
  char key = keypress.getKey();      //Keypad Password Check process begins.
  
  if (key)       // If Key is pressed
  {
   if(i == 0)
   {
    delay(100);
    lcd.clear();
   }
   
    passcheck[i]=key;
     
     if(key == '#')     //'#' Key as Backspace function.
     {
      backSpace();    //User defined function.
      
      lcd.setCursor(0, 1);
      lcd.print(passlen-i);
      lcd.setCursor(2, 1);
      lcd.print("Character Left");
     }

     else if(key == '*')
      break;
      
     else
     {
      lcd.setCursor(i, 0);
      lcd.print(key);      //Print pressed key on LCD.
      i++;

      lcd.setCursor(0, 1);
      lcd.print(passlen-i);
      lcd.setCursor(2, 1);
      lcd.print("Character Left");
     }
    }

 }  

  match=0;
  match = checkPassword();    //User defined function.
 
  if(match == 1)      //Verifying Password.
  {
    for(int j = 0; j < 2; j++)
    {
     lcd.setCursor(3,0);
     lcd.print("Password");
     lcd.setCursor(4,1);
     lcd.print("Match!");
     delay(1000);
     lcd.clear();
     delay(400);
    }
    
    lcd.setCursor(0,0);
    lcd.print(">>>>ACCESS<<<<");
    lcd.setCursor(0,1);
    lcd.print(">>>>GRANTED<<<<");
     delay(1000);
    lcd.setCursor(0,0);
    lcd.print("<<<<ACCESS>>>>");
    lcd.setCursor(0,1);
    lcd.print("<<<<GRANTED>>>>"); 
    delay(4000);
    lcd.clear();
    i=0;
    goto back;
  }
  
  else
  {
    if(match == 2)
      goto here;
    for(int j = 0; j < 2; j++)
    {
     lcd.setCursor(3,0);
     lcd.print("Incorrect");
     lcd.setCursor(3,1);
     lcd.print("Password!");
     delay(1000);
     lcd.clear();
     delay(200);
    }
    i=0;
    lcd.clear();
    goto here; 
  }  
}


//*********************************************************************************************************************



int getId()      //Function to get the UID of the card.
{    
  if(!rc.PICC_IsNewCardPresent())
    return 0; 
  
  if(!rc.PICC_ReadCardSerial())
    return 0;

  for (byte q = 0; q < rc.uid.size; q++) 
    readcard[q]=rc.uid.uidByte[q];


  //---------------READING DATA BLOCK BEGINS----------------------------------------------------
   byte len = 18; 
 //  Serial.println(F("\n**Start Reading**\n"));
   
   status = rc.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumber, &key, &(rc.uid));
   if (status != MFRC522::STATUS_OK) 
    {
    // Serial.print(F("Authentication failed! "));
      return 1;
    }

    status = rc.MIFARE_Read(blockNumber, buffer1, &len);
    if (status != MFRC522::STATUS_OK) 
    {
   //  Serial.print(F("Reading failed! "));
     return 1;
    }

    value = "";
    for (uint8_t q = 0; q < 16; q++)
        value += (char)buffer1[q];
    value.trim();
    
   // Serial.print(value);
   // Serial.println(F("\n**End Reading**\n"));
    delay(1000);
    rc.PICC_HaltA();
    rc.PCD_StopCrypto1();

  //-----------------DATA BLOCK READING ENDS---------------------------------------------------

  lcd.clear(); 
  rc.PICC_HaltA();
  
  return 1;
}


//*************************************************************************************************************************



int isMatch()      //Function to Compare the current tag with pre defined tags.
{
  int ret = 0;
  for(int q=0; q<N; q++)
  {
    lcd.clear();
    lcd.print("  Verifying");
    delay(200);
    lcd.setCursor(11, 0);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);   
    lcd.clear();
    
    if(!memcmp(readcard, defcard[q], 4)) 
      ret = 1;   
  }  
  return ret;
}


//************************************************************************************************************************



void backSpace()       //Function for Backspace in keypad.
{
    i--;
    if(i == -1)
      i=0; 
      
    lcd.setCursor(i, 0);
    lcd.print(" ");
}


//************************************************************************************************************************



int checkPassword()      //Function for Checking Password.
{
  int ret=0;

  if(i != passlen)        //If password length doesnt match.
  {
   lcd.clear();
   lcd.setCursor(3,0);
   lcd.print("Incorrect");
   lcd.setCursor(3,1);
   lcd.print("Password!");
   delay(1000);
   i=0;
   return 2;
  }
  
  for(int j = 0; j < passlen; j++)         //Comparing the password.
  {
    if(passcheck[j] == password[j])
      ret = 1;
    else
    {
      ret = 0;
      break;
    }
  }   

  lcd.clear();
  lcd.print("  Verifying");
  delay(300);
  lcd.setCursor(11, 0);
  lcd.print(".");
  delay(300);   
  lcd.print(".");
  delay(300);
  lcd.print(".");
  delay(700);
  lcd.clear();

  return ret;
}
