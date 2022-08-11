#include <SoftwareSerial.h>
#define MSR A0
SoftwareSerial mySerial(2,3);    // rx is on 2nd pin, tx is on 3rd pin
unsigned int Mwrite;
void setup()
{
  mySerial.begin(9600);
}

void loop() 
{
  Mwrite=map(analogRead(MSR),0,876,0,100);    //scaling moisture in a level from 0 to 100
  mySerial.write(Mwrite);           // sending the moisture level to the 3rd arduino
}
