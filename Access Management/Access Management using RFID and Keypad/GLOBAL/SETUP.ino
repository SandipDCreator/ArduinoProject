void setup() 
{
    
  lcd.begin(16, 2);     
  lcd.backlight();

  SPI.begin();
  rc.PCD_Init();      //Initialize the RFID receiver.  
  
  for (byte q = 0; q < 6; q++) 
     key.keyByte[q] = 0xFF;   
        
}
