void backSpace()       //Function for Backspace in keypad.
{
    i--;
    if(i == -1)
      i = 0; 
      
    lcd.setCursor(i, 0);
    lcd.print(" ");
}

