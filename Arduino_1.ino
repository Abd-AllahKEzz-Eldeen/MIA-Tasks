#include <Wire.h>
#define TSR A0
unsigned int Temp;
void setup()
{
  Wire.begin(8);    // slave's adress is 8
  Wire.onRequest(requestEvent);   // slave is sending
}

void loop()
{
  Temp=map(analogRead(A0),103,310,0,100);   //scaling the temperature between 0,100 C
}

void requestEvent()
{
  if(Temp<100)              // if 0<temperature<100 send it to the master
   Wire.write(Temp);
}
