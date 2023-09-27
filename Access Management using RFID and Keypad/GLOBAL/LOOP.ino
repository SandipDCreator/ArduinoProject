void loop() 
{
  //---------------------------RFID part Begins.--------------------------------
  
  back:            
  while(!getId())         //getId() is user defined function.
  {
    lcd.setCursor(0, 0);
    lcd.print("Scan Access Card");
  }

   match = 0;
   match = isMatch();    //isMatch() is user defined function.
  
   if(match == 1) 
   {       
      lcd.setCursor(5, 0);
      lcd.print("CARD");
      lcd.setCursor(2, 1);
      lcd.print("AUTHORISED!");
      delay(2000);
      lcd.clear();
      delay(200);

      lcd.setCursor(4, 0);       //Welcome message.
      lcd.print("Welcome");
      delay(400);  

      if(value[0] == 0)
      {
        lcd.setCursor(3, 1);             
        lcd.print("New  User");
      }
      else
      {  
        for (int j = 0; j < 16; j++)   //Print the Data block contents.
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
       for(int j = 0; j < 2; j++) 
       {
         lcd.setCursor(5, 0);
         lcd.print("CARD");
         lcd.setCursor(0, 1);
         lcd.print("NOT AUTHORISED!");
         delay(1000);
         lcd.clear();
         delay(500);
       }
       goto back;
     }     


 //---------------------------Password part Begins.---------------------------------

 here:               
 while(i < (passlen+1))
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
   
    passcheck[i] = key;
     
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

  match = 0;
  match = checkPassword();    //User defined function.
 
  if(match == 1)      //Verifying Password.
  {
    for(int j = 0; j < 2; j++)
    {
     lcd.setCursor(3, 0);
     lcd.print("Password");
     lcd.setCursor(4, 1);
     lcd.print("Match!");
     delay(800);
     lcd.clear();
     delay(200);
    }
    
    lcd.setCursor(0, 0);          //Final Access Granted Messsage.
    lcd.print(">>>>ACCESS<<<<<<");
    lcd.setCursor(0, 1);
    lcd.print(">>>>GRANTED<<<<<");
     delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("<<<<ACCESS>>>>>>");
    lcd.setCursor(0, 1);
    lcd.print("<<<<GRANTED>>>>>"); 
    delay(4000);
    lcd.clear();
    i = 0;
  }
  
  else
  {
    if(match == 2)
      goto here;
    for(int j = 0; j < 2; j++)
    {
     lcd.setCursor(3, 0);
     lcd.print("Incorrect");
     lcd.setCursor(3, 1);
     lcd.print("Password!");
     delay(1000);
     lcd.clear();
     delay(200);
    }
    i = 0;
    lcd.clear();
    goto here; 
  }  
}
