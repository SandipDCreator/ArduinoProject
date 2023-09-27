int count=0;
void setup() {
 Serial.begin(9600);
}

void loop(){
  if(Serial.available())
  {
   count=0;
   {
    char input = Serial.read();
    Serial.print(input);
    count++;
    delay(5);
   }
   Serial.println();
   Serial.print("Tag Length: ");
   Serial.print(count);
   Serial.println(" Bytes");
  }
}
