/*-----------------------------------------------------------------------------------------------------------------------


This Project uses:
1. A MFRC522 RFID Reader along with 2 Mifare 1K Tags(a card and a keychain).
2. A 4*4 KEYPAD.
3. A 16*2 I2C LCD. 
4. An Arduino Uno.
5. USB-TTL Converter (For Uploading Programs).
6. Jumper Wires (M-M, M-F).


PIN Connections (To Arduino):
1. I2C LCD (4 Pins)
      SCL--A5-Pin 19
      SDA--A4-Pin 18
      VCC--5v
      GND--GND

2. Keypad (8 Pins)
      Left to Right--Pin 9 to Pin 2
                   (Pin 9 to Pin 6-Rows, Pin 5 to Pin 2-Columns)

3. MFRC522
      SDA--Pin 10
      SCK--Pin 13
      MOSI--Pin 11
      MISO--Pin 12
      IRQ--NIL
      GND--GND
      RST--A0-Pin 14
      3.3V--3.3V

4. USB-TTL Converter
      DTR--Reset(If not working, keep disconnected)(**Hold Reset Button on Arduino while uploading program to emulate the reset**)
      RXD--TXD
      TXD--RXD
      5V--Vin
      GND--GND
      3V3--NIL

-----------------------------------------------------------------------------------------------------------------------*/



//----------------------------------------------LCD------------------------------------------------------------------------

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//----------------------------------------------RFID-----------------------------------------------------------------------

#include <SPI.h>
#include <MFRC522.h>


#define RSTPIN 14      //RFID MFRC522 pin connections.
#define SSPIN 10

MFRC522 rc(SSPIN, RSTPIN);
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;


const byte defcard[][4] = {{0xE5, 0xA7, 0xFA, 0xC2}, {0xE0, 0x0E, 0x7E, 0x1B}};    //Multiple cards.

const int N = 2;      //Number of cards to be used.

byte readcard[4];   

//---------------------------------------------Keypad----------------------------------------------------------------------

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

byte rowPins[ROWS] = {9, 8, 7, 6};     //Connection to Arduino Pins.
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypress = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//-----------------------------------------------------------------------------------------------------------------------


//---------------------------Variables for Reading Data From RFID Card----------------------------------------------------

const byte blockNumber = 2;    //Block number to be read.
byte buffer1[18];      //Array for reading a block. MIFARE_Read method requires at least 18 bytes to hold 16 bytes of a block.
String value = "";    //String stores the Data in the card as human readable characters.


//--------------------------------------Variables for Password part-------------------------------------------------------

int i = 0, match = 0;   
const char password[9] = {'1', '7', '9', '4', 'A', 'B', 'C', 'D'};    //Password for comparison.
char passcheck[9];
const int passlen=8;     //Length of Password.


//------------------------------------------------------------------------------------------------------------------------

 











