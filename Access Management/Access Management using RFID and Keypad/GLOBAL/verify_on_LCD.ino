void verifyPrint()     //Function to Print 'Verifying' on LCD.
{
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
}
