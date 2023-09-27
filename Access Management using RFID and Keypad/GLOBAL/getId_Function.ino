int getId()      //Function to get the UID of the card.
{    
  if(!rc.PICC_IsNewCardPresent())
    return 0; 
  
  if(!rc.PICC_ReadCardSerial())
    return 0;

  for (byte q = 0; q < rc.uid.size; q++) 
    readcard[q] = rc.uid.uidByte[q];


  //---------------READING DATA BLOCK BEGINS---------------------------------------------------- //Keep Read Data Process inside getId() or else it wont work.
  
   byte len = 18;               
   
   status = rc.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumber, &key, &(rc.uid));
   if (status != MFRC522::STATUS_OK)   
      return 1;

   status = rc.MIFARE_Read(blockNumber, buffer1, &len);
   if (status != MFRC522::STATUS_OK) 
      return 1;

   value = "";
   for (uint8_t q = 0; q < 16; q++)
       value += (char)buffer1[q];
   value.trim();
       
   delay(1000);
   rc.PICC_HaltA();
   rc.PCD_StopCrypto1();

  //-----------------DATA BLOCK READING ENDS---------------------------------------------------

  lcd.clear(); 
  rc.PICC_HaltA();  
  return 1;
}

