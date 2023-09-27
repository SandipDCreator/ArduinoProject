int checkPassword()      //Function for Checking Password.
{
  int ret = 0;

  if(i != passlen)        //If password length doesnt match.
  {
   lcd.clear();
   lcd.setCursor(3, 0);
   lcd.print("Incorrect");
   lcd.setCursor(3, 1);
   lcd.print("Password!");
   delay(1000);
   
   i = 0;
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

  verifyPrint();       //User defined Function.

  return ret;
}

