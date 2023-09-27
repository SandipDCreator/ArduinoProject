int isMatch()      //Function to Compare the current tag with pre defined tags.
{
  int ret = 0;
  
  verifyPrint();      //User defined Function.

  for(int j = 0; j < N; j++)   
    if(!memcmp(readcard, defcard[j], 4)) 
      ret = 1;   
      
  return ret;
}

