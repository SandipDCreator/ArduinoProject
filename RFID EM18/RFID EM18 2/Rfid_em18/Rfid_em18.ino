char tag[] ="1C002492359F"; 
char input[12];        
int count = 0;       
boolean flag = 0;    
int led=2;
int led2=3;
void setup()
{
  Serial.begin(9600);   
  pinMode(led, OUTPUT); 
  pinMode(led2, OUTPUT);
}
void loop()
{
  if(Serial.available())
  {
    count = 0; 
    while(Serial.available() && count < 12) 
    {
      input[count] = Serial.read(); 
      count++; 
      delay(5);
    }
    if(count == 12)  
    {
      count =0;
      flag = 1;
      while(count<12)  
      {
        if(input[count]==tag[count])
         flag = 1; 
        else
         flag= 0;                                   
        count++; 
      }
    }
    if(flag == 1)
    {
      Serial.println("Access Allowed!");
      digitalWrite(led2,HIGH);
      delay(4000);
      digitalWrite(led2,LOW);
    }
    else
    {
      Serial.println("Access Denied"); 
      digitalWrite(led,HIGH);
      delay(4000);
      digitalWrite(led,LOW);
    }
    for(count=0; count<12; count++) 
      input[count]= 'F';
    count = 0;
  }
}
