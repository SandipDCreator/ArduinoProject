#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         14           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

byte blockNumber;
byte len;
byte buffer1[18];


void setup() 
{
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
}


void loop() 
{

for (byte i = 0; i < 6; i++) 
  key.keyByte[i] = 0xFF;       // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.


if ( ! mfrc522.PICC_IsNewCardPresent())   // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    return;

if ( ! mfrc522.PICC_ReadCardSerial())
    return;

Serial.println(F("**Card Detected:**"));

blockNumber = 2;
len = 18;

//int largestModulo4Number=blockNumber/4*4;
//int trailerBlock=largestModulo4Number+3;

//status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 2, &key, &(mfrc522.uid));
if (status != MFRC522::STATUS_OK) 
{
  Serial.print(F("Authentication failed: "));
  return 1;
}

status = mfrc522.MIFARE_Read(blockNumber, buffer1, &len);
if (status != MFRC522::STATUS_OK) 
{
  Serial.print(F("Reading failed: "));
  return 1;
}

String value = "";
for (uint8_t i = 0; i < 16; i++)
    value += (char)buffer1[i];
value.trim();
Serial.print(value);
Serial.println(F("\n**End Reading**\n"));
delay(1000);
mfrc522.PICC_HaltA();
mfrc522.PCD_StopCrypto1();
}

