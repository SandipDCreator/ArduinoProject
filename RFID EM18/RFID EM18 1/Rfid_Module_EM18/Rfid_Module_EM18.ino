int count=0;
char input[12];
boolean flag=0;
void setup() {
 Serial.begin(9600);
// pinMode(13, OUTPUT);
// pinMode(8, OUTPUT);
}

void loop(){
  if(Serial.available())
  {
   count=0;
   while(Serial.available() && count<12)
   {
    input[count] = Serial.read();
    count++;
    delay(5);
   }
   Serial.print(input);
   if(input[0]^input[2]^input[4]^input[6]^input[8]==input[10] && input[1]^input[3]^input[5]^input[7]^input[9]==input[11])
   {
    Serial.println("No Error");
  //  digitalWrite(8, HIGH); 
   }
   else
   {
    Serial.println("Error");
   // digitalWrite(13, HIGH);
   }
  }
}
