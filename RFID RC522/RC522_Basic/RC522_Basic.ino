
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

#define RSTPIN 14
#define SSPIN 10
MFRC522 rc(SSPIN, RSTPIN);        //creating mfrc522 instance

int readsuccess=0;

//byte defcard[4]={0x32,0xD7,0x0F,0x2B};    // if you only want one card
byte defcard[][4]={{0xE5,0xA7,0xFA,0xC2}, {0xE0,0x0E,0x7E,0x1B}};         //for multiple cards
int N=2;          //change this to the number of cards/tags you will use
byte readcard[4];           //stores the UID of current tag which is read



void setup() 
{
Serial.begin(9600);

SPI.begin();
rc.PCD_Init();        //initialize the receiver  
rc.PCD_DumpVersionToSerial();         //show details of card reader module

Serial.println(F("The Authorised cards are: "));        //display authorised cards just to demonstrate you may comment this section out

for(int i=0; i<N; i++){ 
  Serial.print(i+1);
  Serial.print(".  ");
  
  for(int j=0; j<4; j++){
    Serial.print(defcard[i][j] < 0x10 ? " 0" : " ");   //Important step
    Serial.print(defcard[i][j], HEX);
  }
  Serial.println("");
 }
Serial.println("");  

Serial.println(F("Scan Access Card to see Details."));
}



void loop() 
{  
  readsuccess = getid();
  if(readsuccess)
  {
   int match=0;

   for(int i=0; i<N; i++)         //this is the part where compare the current tag with pre defined tags
   {
     Serial.print("Testing Against Authorised card no: ");
     Serial.println(i+1);
     if(!memcmp(readcard, defcard[i], 4))
       match++;   
   }    
  
   if(match)
     Serial.println("\nCARD AUTHORISED\n\n");  
      
   else
     Serial.println("\nCARD NOT AUTHORISED\n");        
  }
}


int getid()           //function to get the UID of the card
{    
  if(!rc.PICC_IsNewCardPresent())
    return 0; 
  if(!rc.PICC_ReadCardSerial())
    return 0;
  
  Serial.println("The UID of the Scanned Card is:");
  
  for(int i=0; i<4; i++)
  {   
    readcard[i]=rc.uid.uidByte[i];         //storing the UID of the tag in readcard
    Serial.print(readcard[i], HEX);   
  }  

  Serial.print(F("Card UID:"));
   
  for (byte i = 0; i < rc.uid.size; i++) 
  {
    readcard[i]=rc.uid.uidByte[i];
    Serial.print(rc.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rc.uid.uidByte[i], HEX);
  } 
  
  Serial.println("");
  
  rc.PICC_HaltA();
  
  return 1;
}



